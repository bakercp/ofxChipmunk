#include "ofxChipmunkCircle.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

Circle::Circle(){

}

Circle::Circle(cpSpace *space, float radius, float mass){
    setup(space, radius, mass);
}

Circle::Circle(ShapeCircle *src, float mass){
    cpFloat moment = cpMomentForCircle(mass, 0, src->getRadius(), toChipmunk(src->getOffset()));
    DynamicBody::setup(cpShapeGetSpace(src->shape), mass, moment);
    ShapeCircle::setup(src);
    cpShapeSetBody(shape, body);
}

void Circle::setup(cpSpace *space, float radius, float mass){
    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
    DynamicBody::setup(space, mass, moment);
    ShapeCircle::setup(space, body, radius);
}

} // namespace ofxChipmunk
