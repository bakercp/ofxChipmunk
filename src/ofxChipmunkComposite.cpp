#include "ofxChipmunkComposite.h"

namespace ofxChipmunk {

Composite::Composite(){

}

Composite::Composite(cpSpace *space, Composite::Definition &def){
	setup(space, def);
}

void Composite::setup(cpSpace* space, Definition& def){
	Body::setup(space, def.getMass(), def.getMoment());
	for(auto d: def.shapes){
		add(d->create(space, body));
	}
}

void Composite::add(Shape *shape){
	shapes.push_back(std::shared_ptr<Shape>(shape));
}

///////////////////////////////////////////

void Composite::Definition::addCircle(float radius, ofVec2f offset, float mass, float f, float e){
	shapes.push_back(new CircleDefinition(radius, offset, mass, f, e));
}

void Composite::Definition::addRect(ofRectangle rect, float mass, float f, float e){
	shapes.push_back(new RectDefinition(rect, mass, f, e));
}

void Composite::Definition::addPolygon(ofPolyline poly, float mass, float f, float e){
	std::vector<ofVec2f> vecs;
	for(auto& p: poly){
		vecs.push_back(p);
	}
	addPolygon(vecs, mass, f, e);
}

void Composite::Definition::addPolygon(std::vector<ofVec2f> points, float mass, float f, float e){
	shapes.push_back(new PolygonDefinition(points, mass, f, e));
}

void Composite::Definition::addLine(ofVec2f a, ofVec2f b, float mass, float f, float e){

}

cpFloat Composite::Definition::getMass(){
	cpFloat totalMass = 0;
	for(auto s: shapes){
		totalMass += s->mass;
	}
	return totalMass;
}

cpFloat Composite::Definition::getMoment(){
	cpFloat totalMoment = 0;
	for(auto s: shapes){
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

Shape *Composite::Definition::CircleDefinition::create(cpSpace *space, cpBody *body){
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

Shape *Composite::Definition::RectDefinition::create(cpSpace *space, cpBody *body){
	return new ShapeRect(space, body, bounds);
}

//
Composite::Definition::PolygonDefinition::PolygonDefinition(std::vector<ofVec2f> p, float m, float f, float e){
	mass = m;
	points = p;
	friction = f;
	elasticity = e;
	moment = cpMomentForPoly(mass, points.size(), toChipmunk(points).data(), toChipmunk(ofVec2f(0,0)), 0);
}

Shape *Composite::Definition::PolygonDefinition::create(cpSpace *space, cpBody *body){
	ShapePolygon* sp = new ShapePolygon(space, body, points);
	sp->setElasticity(elasticity);
	sp->setFriction(friction);
}

} // namespace ofxChimpunk
