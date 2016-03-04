#ifndef OFXCHIMPUNK_BODY_H
#define OFXCHIMPUNK_BODY_H

#include "ofMain.h"
#include <chipmunk.h>
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class Body{
public:
	Body();
	~Body();

	void setup(cpSpace* space, float mass, cpFloat moment);

	ofVec2f getPosition();
	void setPosition(ofVec2f pos);

	bool isSleeping();


	cpBody* body;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
