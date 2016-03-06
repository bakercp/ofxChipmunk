#ifndef OFXCHIMPUNK_SHAPE_H
#define OFXCHIMPUNK_SHAPE_H

#include "ofMain.h"
#include <chipmunk.h>
#include "chipmunk_unsafe.h"


namespace ofxChipmunk {

class Shape {
public:
    Shape();
	~Shape();

    void setup(cpSpace* space, cpShape* shape);

    void setElasticity(float);
	void setFriction(float friction);

protected:
    cpShape* shape;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
