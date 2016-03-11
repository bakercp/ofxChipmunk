#include "ofxChipmunkShape.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

Shape::Shape():shape(nullptr){

}

Shape::~Shape(){
	cpSpaceRemoveShape(cpShapeGetSpace(shape), shape);
	cpShapeFree(shape);
}

void Shape::setup(cpSpace *space, cpShape *s){
	shape = cpSpaceAddShape(space, s);
	setFriction(OFXCHIPMUNK_DEFAULT_FRICTION);
	setElasticity(OFXCHIPMUNK_DEFAULT_ELASTICITY);
}

void Shape::setElasticity(float value){
	cpShapeSetElasticity(shape, value);
}

void Shape::setFriction(float friction){
	cpShapeSetFriction(shape, friction);
}

//
ShapeCircle::ShapeCircle(){

}

ShapeCircle::ShapeCircle(cpSpace *space, cpBody *body, float radius, ofVec2f offset){
	setup(space, body, radius, offset);
}

void ShapeCircle::setup(cpSpace *space, cpBody* body, float radius, ofVec2f offset){
	radiusInitial = radius;
	offsetInitial = offset;
	Shape::setup(space, cpCircleShapeNew(body, radius, toChipmunk(offset)));
}

void ShapeCircle::setRadius(float r){
	cpCircleShapeSetRadius(shape, r);
}

void ShapeCircle::setOffset(ofVec2f off){
	cpCircleShapeSetOffset(shape, toChipmunk(off));
}

float ShapeCircle::getRadius(){
	return cpCircleShapeGetRadius(shape);
}

void ShapeCircle::scale(float s){
	setRadius(radiusInitial*s);
	setOffset(offsetInitial*s);
}

ofPath ShapeCircle::getAsPath(){
	ofPath ret;
	ret.circle(toOf(cpCircleShapeGetOffset(shape)), getRadius());
}

//
ShapeRect::ShapeRect(){

}

ShapeRect::ShapeRect(cpSpace *space, cpBody *body, ofRectangle bounds){
	setup(space, body, bounds);
}

void ShapeRect::setup(cpSpace *space, cpBody *body, ofRectangle bounds){
	Shape::setup(space, cpBoxShapeNew(body, bounds.width, bounds.height, 0));
}

//
ShapePolygon::ShapePolygon(){numPoints=0;}

ShapePolygon::ShapePolygon(cpSpace *space, cpBody *body, ofPolyline poly){
	numPoints=0;
	setup(space, body, poly);
}

ShapePolygon::ShapePolygon(cpSpace *space, cpBody *body, std::vector<ofVec2f> &points){
	numPoints = 0;
	setup(space, body, points);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, ofPolyline poly){
	std::vector<ofVec2f> vecs;
	for(auto& p: poly){
		vecs.push_back(p);
	}
	setup(space, body, vecs);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, std::vector<ofVec2f> &points){
	setup(space, body, points.size(), toChipmunk(points).data());
}

void ShapePolygon::scale(float s){

	/*
	int nPts = cpPolyShapeGetCount(shape);

	std::vector<cpVect> pts(nPts);
	for(int i=0; i<nPts; i++){
		pts.push_back(cpvmult(cpPolyShapeGetVert(shape, i), s));
	}
	*/

	std::vector<cpVect> pts;
	for(int i=0; i<numPoints; i++){
		pts.push_back(cpvmult(points[i], s));
	}

	//cpPolyShapeSetVerts(shape, numPoints, pts.data(), cpTransformIdentity);
	cpPolyShapeSetVertsRaw(shape, numPoints, pts.data());
}

ofPath ShapePolygon::getAsPath(){
	ofPath ret;
	for(int i=0; i<cpPolyShapeGetCount(shape); i++){
		ret.lineTo(toOf(cpPolyShapeGetVert(shape, i)));
	}
	ret.close();
	return ret;
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, int nPoints, cpVect *verts){
	if(numPoints>0){
		delete[] points;
	}

	/*
	numPoints = nPoints;
	points = new cpVect[numPoints];
	memcpy(points, verts, numPoints*sizeof(cpVect));
	*/

	Shape::setup(space, cpPolyShapeNew(body, nPoints, verts, cpTransformIdentity, 0.0));


	numPoints = cpPolyShapeGetCount(shape);
	points = new cpVect[numPoints];
	for(int i=0;i<numPoints;i++){
		points[i] = cpPolyShapeGetVert(shape, i);
	}
}

//

} // namespace ofxChimpunk
