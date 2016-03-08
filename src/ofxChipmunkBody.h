#ifndef OFXCHIMPUNK_BODY_H
#define OFXCHIMPUNK_BODY_H

#include "ofMain.h"
#include <chipmunk.h>
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class BaseBody{
protected:
	BaseBody();
	~BaseBody();

	void setup(cpSpace* space, cpBody* body);

public:
	ofVec2f getPosition();
	void setPosition(ofVec2f pos);
	float getRotation();
	void setRotation(float radians);
	bool isSleeping();

	cpBody* body;
};

class Body: public BaseBody{
public:
	Body();
	~Body();

	void setup(cpSpace* space, float mass, cpFloat moment);
};

class StaticBody: public BaseBody{
public:
	StaticBody();
	StaticBody(cpSpace* space);

	void setup(cpSpace* space);
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
