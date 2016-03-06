#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

Constraint::Constraint(){

}

void Constraint::setup(cpSpace* space, cpConstraint *c){
    constraint = c;
	cpSpaceAddConstraint(space, constraint);
}



} // namespace ofxChipmunk
