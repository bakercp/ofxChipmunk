#include "ofxChipmunkCircle.h"

namespace ofxChipmunk {

Circle::Circle()
{

}

Circle::Circle(cpSpace *space, float radius, float mass){
	setup(space, radius, mass);
}

void Circle::setup(cpSpace *space, float radius, float mass){
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
	Body::setup(space, mass, moment);
	Shape::setup(space, cpCircleShapeNew(body, radius, cpvzero));
}

void Circle::setRadius(float r){
	cpCircleShapeSetRadius(shape, r);
}

float Circle::getRadius(){
	return cpCircleShapeGetRadius(shape);
}

} // namespace ofxChipmunk
