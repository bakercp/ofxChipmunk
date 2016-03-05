#include "ofxChipmunkShape.h"

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

} // namespace ofxChimpunk
