#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

Constraint::Constraint():constraint(nullptr){

}

Constraint::~Constraint(){
	if(constraint){
		cpSpaceRemoveConstraint(cpConstraintGetSpace(constraint), constraint);
		cpConstraintDestroy(constraint);
	}
}

void Constraint::setup(cpSpace* space, cpConstraint *c){
    constraint = c;
	cpSpaceAddConstraint(space, constraint);
}

} // namespace ofxChipmunk
