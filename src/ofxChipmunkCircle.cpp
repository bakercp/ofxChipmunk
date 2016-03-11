#include "ofxChipmunkCircle.h"

namespace ofxChipmunk {

Circle::Circle(){

}

Circle::Circle(cpSpace *space, float radius, float mass){
	setup(space, radius, mass);
}

void Circle::setup(cpSpace *space, float radius, float mass){
    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
    DynamicBody::setup(space, mass, moment);
    ShapeCircle::setup(space, body, radius);
}

} // namespace ofxChipmunk
