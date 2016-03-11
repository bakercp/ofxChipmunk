#include "ofxChipmunkPivotJoint.h"

namespace ofxChipmunk {

PivotJoint::PivotJoint(){

}


PivotJoint::PivotJoint(cpSpace *space, Body *bodyA, Body *bodyB, ofVec2f anchorA, ofVec2f anchorB){
	setup(space, bodyA, bodyB, anchorA, anchorB);
}

void PivotJoint::setup(cpSpace *space, Body *bodyA, Body *bodyB, ofVec2f anchorA, ofVec2f anchorB){
	Constraint::setup(space, cpPivotJointNew2(bodyA->body, bodyB->body, toChipmunk(anchorA), toChipmunk(anchorB)));
}

} // namespace ofxChipmunk
