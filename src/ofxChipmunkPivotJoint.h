#ifndef OFXCHIPMUNK_PIVOTJOINT_H
#define OFXCHIPMUNK_PIVOTJOINT_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

class PivotJoint: public Constraint{
public:
	PivotJoint();
	PivotJoint(cpSpace* space, Body* bodyA, Body* bodyB, glm::vec2 anchorA=glm::vec2(0,0), glm::vec2 anchorB=glm::vec2(0,0));

	void setup(cpSpace* space, Body* bodyA, Body* bodyB, glm::vec2 anchorA=glm::vec2(0,0), glm::vec2 anchorB=glm::vec2(0,0));
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_PIVOTJOINT_H
