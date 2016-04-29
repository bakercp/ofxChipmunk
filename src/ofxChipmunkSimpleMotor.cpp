#include "ofxChipmunkSimpleMotor.h"

namespace ofxChipmunk {

SimpleMotor::SimpleMotor(){

}

SimpleMotor::SimpleMotor(cpSpace *space, Body *a, Body *b, float rate){
	setup(space, a->body, b->body, rate);
}

SimpleMotor::SimpleMotor(cpSpace *space, cpBody *a, cpBody *b, float rate){
	setup(space, a, b, rate);
}

void SimpleMotor::setup(cpSpace *space, Body *a, Body *b, float rate){
	setup(space, a->body, b->body, rate);
}

void SimpleMotor::setup(cpSpace *space, cpBody *a, cpBody *b, float rate){
	Constraint::setup(space, cpSimpleMotorNew(a, b, rate));
}

void ofxChipmunk::SimpleMotor::setRate(float rate){
	cpSimpleMotorSetRate(constraint,  rate);
}

float ofxChipmunk::SimpleMotor::getRate(){
	return cpSimpleMotorGetRate(constraint);
}

} // namespace ofxChipmunk
