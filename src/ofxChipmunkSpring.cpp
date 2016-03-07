#include "ofxChipmunkSpring.h"

namespace ofxChipmunk {

Spring::Spring(){

}

Spring::Spring(cpSpace *space, Body *a, Body *b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	setup(space, a, b, anchorA, anchorB, distance, stiffness, damping);
}

Spring::Spring(cpSpace *space, cpBody *a, cpBody *b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	setup(space, a, b, anchorA, anchorB, distance, stiffness, damping);
}

void Spring::setup(cpSpace* space, Body *a, Body *b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	setup(space, a->body, b->body, anchorA, anchorB, distance, stiffness, damping);
}

void Spring::setup(cpSpace *space, cpBody *a, cpBody *b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	Constraint::setup(space, cpDampedSpringNew(a, b, toChipmunk(anchorA), toChipmunk(anchorB), distance, stiffness, damping));
}

} // namespace ofxChipmunk
