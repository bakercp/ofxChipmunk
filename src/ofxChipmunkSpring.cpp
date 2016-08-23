#include "ofxChipmunkSpring.h"

namespace ofxChipmunk {

Spring::Spring():forceFunction(nullptr){

}

Spring::Spring(cpSpace *space, Body *a, Body *b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness, float damping){
	setup(space, a, b, anchorA, anchorB, distance, stiffness, damping);
}

Spring::Spring(cpSpace *space, cpBody *a, cpBody *b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness, float damping){
	setup(space, a, b, anchorA, anchorB, distance, stiffness, damping);
}

void Spring::setup(cpSpace* space, Body *a, Body *b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness, float damping){
	setup(space, a->body, b->body, anchorA, anchorB, distance, stiffness, damping);
}

void Spring::setup(cpSpace *space, cpBody *a, cpBody *b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness, float damping){
	Constraint::setup(space, cpDampedSpringNew(a, b, toChipmunk(anchorA), toChipmunk(anchorB), distance, stiffness, damping));
}

float Spring::getStiffness(){
	return cpDampedSpringGetStiffness(constraint);
}

float Spring::getLength(){
	return cpDampedSpringGetRestLength(constraint);
}

void Spring::setLength(float length){
	cpDampedSpringSetRestLength(constraint,length);
}

void Spring::setStiffness(float stiffness){
	cpDampedSpringSetStiffness(constraint, stiffness);
}

void Spring::setSpringForceFunction(Spring::ForceFunction f){
	cpConstraintSetUserData(constraint, this);
	cpDampedSpringSetSpringForceFunc(constraint, &Spring::springForceFunc);
}

cpFloat Spring::springForceFunc(cpConstraint *constraint, cpFloat dist){
	Spring* spring = (Spring*)cpConstraintGetUserData(constraint);
	if(spring->forceFunction){
		return spring->forceFunction(spring, dist);
	}
	return 0;
}


} // namespace ofxChipmunk
