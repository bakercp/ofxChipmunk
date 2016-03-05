#ifndef OFXCHIPMUNK_CIRCLE_H
#define OFXCHIPMUNK_CIRCLE_H

#include "ofxChipmunkShape.h"
#include "ofxChipmunkBody.h"

namespace ofxChipmunk {

class Circle: public ofxChipmunk::Body, public ofxChipmunk::Shape{
public:
    Circle();
	Circle(cpSpace* space, float radius, float mass=1);

	void setup(cpSpace* space, float radius, float mass=1);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_CIRCLE_H
