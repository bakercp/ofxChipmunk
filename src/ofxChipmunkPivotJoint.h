#ifndef OFXCHIPMUNK_PIVOTJOINT_H
#define OFXCHIPMUNK_PIVOTJOINT_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

class PivotJoint: public Constraint{
public:
	PivotJoint();
	PivotJoint(cpSpace* space, Body* bodyA, Body* bodyB, ofVec2f anchorA=ofVec2f(0,0), ofVec2f anchorB=ofVec2f(0,0));

	void setup(cpSpace* space, Body* bodyA, Body* bodyB, ofVec2f anchorA=ofVec2f(0,0), ofVec2f anchorB=ofVec2f(0,0));
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_PIVOTJOINT_H
