#include "ofxChipmunkPivotJoint.h"

namespace ofxChipmunk {

PivotJoint::PivotJoint(){

}


PivotJoint::PivotJoint(cpSpace *space, Body *bodyA, Body *bodyB, glm::vec2 anchorA, glm::vec2 anchorB){
	setup(space, bodyA, bodyB, anchorA, anchorB);
}

void PivotJoint::setup(cpSpace *space, Body *bodyA, Body *bodyB, glm::vec2 anchorA, glm::vec2 anchorB){
	Constraint::setup(space, cpPivotJointNew2(bodyA->body, bodyB->body, toChipmunk(anchorA), toChipmunk(anchorB)));
}

} // namespace ofxChipmunk
