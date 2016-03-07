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

class ShapeCircle: public Shape{
public:
    void setup(cpSpace* space, cpBody* body, float radius);
    void setRadius(float r);
    float getRadius();
};

class ShapeRect: public Shape{
public:
    void setup(cpSpace* space, cpBody* body, ofRectangle bounds);
};

class ShapePolygon: public Shape{
public:
    void setup(cpSpace* space, cpBody* body, ofPolyline poly);
    void setup(cpSpace* space, cpBody* body, std::vector<ofVec2f>& points);
protected:
    void setup(cpSpace* space, cpBody* body, int nPoints, cpVect* pts);
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
