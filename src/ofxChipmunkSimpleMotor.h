#ifndef OFXCHIPMUNKSIMPLEMOTOR_H
#define OFXCHIPMUNKSIMPLEMOTOR_H

#include "ofMain.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

class SimpleMotor: public Constraint
{
public:

	SimpleMotor();
	SimpleMotor(cpSpace *space, Body *a, Body *b, float rate=1);
	SimpleMotor(cpSpace *space, cpBody *a, cpBody *b, float rate=1);

	void setup(cpSpace* space, Body* a, Body* b, float rate=1);
	void setup(cpSpace* space, cpBody* a, cpBody* b, float rate=1);

	void setRate(float rate);
	float getRate();

};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNKSIMPLEMOTOR_H
