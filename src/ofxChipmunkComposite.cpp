#include "ofxChipmunkComposite.h"
#include "ofxChipmunkWorld.h"

extern "C"{
#include <cpPolyline.h>
}

namespace ofxChipmunk {

Composite::Composite(){

}

Composite::Composite(cpSpace *space, Composite::Definition &def){
	setup(space, def);
}

void Composite::setup(cpSpace* s, Definition& def){
	scale = 1;
    space = s;
	if(def.definitions.size() == 0){
		ofLogError("ofxChipmunk::Composite") << "No shape definitions added. Cannot create body.";
		return;
	}
	DynamicBody::setup(space, def.getMass(), def.getMoment());
	for(auto d: def.definitions){
		add(d->create(space, body));
	}
}

void Composite::setFriction(float friction, int id){
	if(id>-1){
		getShape(id)->setFriction(friction);
	}else{
		for(auto s:shapes){
			s->setFriction(friction);
		}	}
}

void Composite::setElasticity(float elasiticity, int id){
	if(id>-1){
		getShape(id)->setElasticity(elasiticity);
	}else{
		for(auto s:shapes){
			s->setElasticity(elasiticity);
		}
	}
}

shared_ptr<Shape> Composite::getShape(int id){
	if(id>=shapes.size()){
		ofLogFatalError("ofxChipmunk::Composite") << "No shape with id " << id;
	}
	return shapes[id];
}

int Composite::getNumShapes(){
	return shapes.size();
}

void Composite::setScale(float scl){
	scale = scl;
	for(auto s: shapes){
		s->scale(scl);
	}
}

ofPath Composite::getAsPath(){
	ofPath ret;
	for(auto s: shapes){
		ret.append(s->getAsPath());
	}
	return ret;
}

void Composite::collisionSetGroup(unsigned int group){
	for(auto s: shapes){
		s->collisionSetGroup(group);
    }
}

std::vector<std::shared_ptr<DynamicBody>> Composite::breakApart(){
    std::vector<std::shared_ptr<DynamicBody>> ret;
    float mass = cpBodyGetMass(body) / float(shapes.size());
    float moment = cpBodyGetMoment(body) / float(shapes.size());
    //ugly hack to get the world
    World* world = (World*)cpSpaceGetUserData(space);
    for(auto shape: shapes){
        ret.push_back(world->createBodyForShape(shape.get()));
        if(ret.back()){
			ret.back()->setPosition(getPosition());
			ret.back()->setRotation(getRotation());
			if(shape->getType() == Shape::Type::Polygon){
				Polygon* poly = (Polygon*)ret.back().get();
				poly->scale(scale);
				ofVec2f offset = poly->getCenter();
				poly->move(offset);
				poly->setOffset(-offset);
			}
        }
    }
    shapes.clear();
    return ret;
}

void Composite::add(Shape *shape){
	shapes.push_back(std::shared_ptr<Shape>(shape));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Composite::Definition::addCircle(float radius, ofVec2f offset, float mass, float f, float e){
	definitions.push_back(shared_ptr<ShapeDefinition>(new CircleDefinition(radius, offset, mass, f, e)));
}

void Composite::Definition::addRect(ofRectangle rect, float mass, float f, float e){
	definitions.push_back(shared_ptr<ShapeDefinition>(new RectDefinition(rect, mass, f, e)));
}

void Composite::Definition::addPolygon(ofPolyline poly, float radius, float mass, float f, float e){
	std::vector<ofVec2f> vecs;
	for(auto& p: poly){
		vecs.push_back(p);
	}
	addPolygon(vecs, radius, mass, f, e);
}

void Composite::Definition::addPolygon(std::vector<ofVec2f> points, float radius, float mass, float f, float e){
	definitions.push_back(shared_ptr<ShapeDefinition>(new PolygonDefinition(points, radius, mass, f, e)));
}

void Composite::Definition::addConcavePolygon(ofPolyline poly, float precision, float radius, float mass, float friction, float elasticity){
	std::vector<ofVec2f> vecs;
	for(auto& p: poly){
		vecs.push_back(p);
	}
	addConcavePolygon(vecs, precision, radius, mass, friction, elasticity);
}

void Composite::Definition::addConcavePolygon(std::vector<ofVec2f> points, float precision, float radius, float mass, float friction, float elasticity){
	//definitions.push_back(shared_ptr<ShapeDefinition>(new ConvexPolygonDefinition(points, precision, mass, friction, elasticity)));
	std::vector<cpVect> verts = toChipmunk(points);
	if(verts[0].x != verts.back().x || verts[0].y != verts.back().y)
		verts.push_back(verts[0]);

	//fix wrong winding
	if(cpAreaForPoly(verts.size(), verts.data(), 0) < 0)
		std::reverse(verts.begin(), verts.end());

	cpPolyline* cpl = (cpPolyline*)calloc(1, sizeof(int)*2+sizeof(cpVect)*verts.size());
	cpl->capacity = verts.size();
	cpl->count = verts.size();

	memcpy(&cpl->verts, verts.data(), sizeof(cpVect)*verts.size());



	cpPolylineSet* set = cpPolylineConvexDecomposition(cpl, precision);

	for(int i=0; i<set->count; i++){
		std::vector<ofVec2f> vec;
		cpPolyline* poly = set->lines[i];
		for(int j=0; j<poly->count; j++){
			vec.push_back(toOf(poly->verts[j]));
		}
		addPolygon(vec, radius, mass, friction, elasticity);
	}

	//ofLogNotice("ofxChipmunk::Composite") << "Split concave polygon into " << set->count << " parts";

	cpPolylineSetFree(set, true);
	cpPolylineFree(cpl);
}

void Composite::Definition::addLine(ofVec2f a, ofVec2f b, float mass, float f, float e){
	ofLogWarning("ofxChipmunk::Composite") << "add line not yet implemented";
}

cpFloat Composite::Definition::getMass(){
	cpFloat totalMass = 0;
	for(auto s: definitions){
		totalMass += s->mass;
	}
	return totalMass;
}

cpFloat Composite::Definition::getMoment(){
	cpFloat totalMoment = 0;
	for(auto s: definitions){
		totalMoment += s->moment;
	}
	return totalMoment;
}

/////////////////////////////////////////////
Composite::Definition::CircleDefinition::CircleDefinition(float r, ofVec2f o, float m, float f, float e){
	radius = r;
	offset = o;
	mass = m;
	friction = f;
	elasticity = e;
	moment = cpMomentForCircle(mass, 0, radius, toChipmunk(offset));
}

Shape* Composite::Definition::CircleDefinition::create(cpSpace *space, cpBody *body){
	return new ShapeCircle(space, body, radius, offset);
}

//
Composite::Definition::RectDefinition::RectDefinition(ofRectangle b, float m, float f, float e){
	bounds = b;
	mass = m;
	friction = f;
	elasticity = e;
	moment = cpMomentForBox2(mass, toChipmunk(bounds));
}

Shape* Composite::Definition::RectDefinition::create(cpSpace *space, cpBody *body){
	return new ShapeRect(space, body, bounds);
}

//
Composite::Definition::PolygonDefinition::PolygonDefinition(std::vector<ofVec2f> p, float r, float m, float f, float e){
	mass = m;
	points = p;
	friction = f;
	elasticity = e;
	radius = r;
	moment = cpMomentForPoly(mass, points.size(), toChipmunk(points).data(), toChipmunk(ofVec2f(0,0)), 0);
}

Shape* Composite::Definition::PolygonDefinition::create(cpSpace *space, cpBody *body){
	ShapePolygon* sp = new ShapePolygon(space, body, points, radius);
	sp->setElasticity(elasticity);
	sp->setFriction(friction);
	return sp;
}


} // namespace ofxChimpunk
