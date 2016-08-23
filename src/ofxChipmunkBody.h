#ifndef OFXCHIMPUNK_BODY_H
#define OFXCHIMPUNK_BODY_H

#include "ofMain.h"
#include <chipmunk.h>
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class Body{
protected:
	Body();
	~Body();

	void setup(cpSpace* space, cpBody* body);

public:
	glm::vec2 getPosition();
	void setPosition(glm::vec2 pos);
	void move(glm::vec2 m);
	float getRotation();
	void setRotation(float radians);
	bool isSleeping();
	void addForce(glm::vec2 force, glm::vec2 localOffset=glm::vec2(0,0));

	cpBody* body;
};

class DynamicBody: public Body{
public:
	DynamicBody();
	~DynamicBody();

	void setup(cpSpace* space, float mass, cpFloat moment);
};

class StaticBody: public Body{
public:
	StaticBody();
	StaticBody(cpSpace* space);

	void setup(cpSpace* space);
};

class KinematicBody: public Body{
public:
	KinematicBody();
	KinematicBody(cpSpace* space);

	void setup(cpSpace* space);
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
