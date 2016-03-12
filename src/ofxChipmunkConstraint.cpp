#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

Constraint::Constraint():constraint(nullptr){

}

Constraint::~Constraint(){
	if(constraint){
		cpSpaceRemoveConstraint(cpConstraintGetSpace(constraint), constraint);
		cpConstraintDestroy(constraint);
		constraint = nullptr;
	}
}

void Constraint::setup(cpSpace* space, cpConstraint *c){
    constraint = c;
	cpSpaceAddConstraint(space, constraint);
	cpConstraintSetUserData(constraint, this);
}

void Constraint::setMaxForce(double force){
	cpConstraintSetMaxForce(constraint, force);
}

void Constraint::setErrorBias(double bias){
	cpConstraintSetErrorBias(constraint, bias);
}

} // namespace ofxChipmunk
