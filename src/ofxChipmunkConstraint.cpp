#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

Constraint::Constraint():constraint(nullptr){

}

Constraint::~Constraint(){
	if(constraint)
		cpConstraintDestroy(constraint);
}

void Constraint::setup(cpSpace* space, cpConstraint *c){
    constraint = c;
	cpSpaceAddConstraint(space, constraint);
	ofLog() << "NEW CONSTRIANT";
}

} // namespace ofxChipmunk
