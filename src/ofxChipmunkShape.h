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
	ShapeCircle();
	ShapeCircle(cpSpace* space, cpBody* body, float radius, ofVec2f offset = ofVec2f(0, 0));
	void setup(cpSpace* space, cpBody* body, float radius, ofVec2f offset = ofVec2f(0, 0));
    void setRadius(float r);
    float getRadius();
};

class ShapeRect: public Shape{
public:
	ShapeRect();
	ShapeRect(cpSpace* space, cpBody* body, ofRectangle bounds);
    void setup(cpSpace* space, cpBody* body, ofRectangle bounds);
};

class ShapePolygon: public Shape{
public:
	ShapePolygon();
	ShapePolygon(cpSpace* space, cpBody* body, ofPolyline poly);
	ShapePolygon(cpSpace* space, cpBody* body, std::vector<ofVec2f>& points);

    void setup(cpSpace* space, cpBody* body, ofPolyline poly);
    void setup(cpSpace* space, cpBody* body, std::vector<ofVec2f>& points);
protected:
    void setup(cpSpace* space, cpBody* body, int nPoints, cpVect* pts);
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
