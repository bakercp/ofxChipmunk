#include "ofxChipmunkShape.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

Shape::Shape():shape(nullptr){

}

Shape::~Shape(){
	cpShapeFree(shape);
}

void Shape::setup(cpSpace *space, cpShape *s){
	shape = cpSpaceAddShape(space, s);
    setFriction(.8);
    setElasticity(.1);
}

void Shape::setElasticity(float value){
    cpShapeSetElasticity(shape, value);
}

void Shape::setFriction(float friction){
    cpShapeSetFriction(shape, friction);
}

//
void ShapeCircle::setup(cpSpace *space, cpBody* body, float radius){
    Shape::setup(space, cpCircleShapeNew(body, radius, cpvzero));
}

void ShapeCircle::setRadius(float r){
    cpCircleShapeSetRadius(shape, r);
}

float ShapeCircle::getRadius(){
    return cpCircleShapeGetRadius(shape);
}

//
void ShapeRect::setup(cpSpace *space, cpBody *body, ofRectangle bounds){
    Shape::setup(space, cpBoxShapeNew(body, bounds.width, bounds.height, 0));
}

//
void ShapePolygon::setup(cpSpace *space, cpBody *body, ofPolyline poly){
    std::vector<ofVec2f> vecs;
    for(auto& p: poly){
        vecs.push_back(p);
    }
    setup(space, body, vecs);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, std::vector<ofVec2f> &points){
    cpVect verts[points.size()];
    //memcpy(verts, points.data(), sizeof(cpVect)*points.size());
    for(size_t i=0; i<points.size(); i++){
        verts[i] = toChipmunk(points[i]);
    }

    setup(space, body, points.size(), verts);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, int nPoints, cpVect *verts){
    Shape::setup(space, cpPolyShapeNew(body, nPoints, verts, cpTransformIdentity, 0.0));
}

//

} // namespace ofxChimpunk
