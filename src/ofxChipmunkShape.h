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

	//very unsafe function
	virtual void scale(float s){ofLogNotice("ofxChipmunk") << "Scale not implemented for this shape";};

	virtual ofPath getAsPath(){ofLogNotice("ofxChipmunk") << "GetAsPath not implemented for this shape";};

	/**
	 * @brief shapes in the same category do not collide with each other
	 * @param group id
	 */
	void collisionSetGroup(unsigned int group);
	unsigned int collisionGetGroup();

	/*
	void collisionSetCategory(unsigned int category);
	void collisionDisableWithCategory(unsigned int category);
	void collisionEnableWithCategory(unsigned int category);
	*/

	void setCollisionType(int typeId);

protected:
	cpShape* shape;
};

class ShapeCircle: public Shape{
public:
	ShapeCircle();
	ShapeCircle(cpSpace* space, cpBody* body, float radius, ofVec2f offset = ofVec2f(0, 0));
	void setup(cpSpace* space, cpBody* body, float radius, ofVec2f offset = ofVec2f(0, 0));
	void setRadius(float r);
	void setOffset(ofVec2f off);
	float getRadius();
	void scale(float s) override;
	ofPath getAsPath() override;
private:
	float radiusInitial;
	ofVec2f offsetInitial;
};

class ShapeRect: public Shape{
public:
	ShapeRect();
	ShapeRect(cpSpace* space, cpBody* body, ofRectangle bounds, float radius=0);
	void setup(cpSpace* space, cpBody* body, ofRectangle bounds, float radius=0);
};

class ShapeLine: public Shape{
public:
	ShapeLine();
	ShapeLine(cpSpace* space, cpBody* body, ofVec2f a, ofVec2f b, float radius=0);
	void setup(cpSpace* space, cpBody* body, ofVec2f a, ofVec2f b, float radius=0);
};

class ShapePolygon: public Shape{
public:
	ShapePolygon();
	ShapePolygon(cpSpace* space, cpBody* body, ofPolyline poly);
	ShapePolygon(cpSpace* space, cpBody* body, std::vector<ofVec2f>& points);

	void setup(cpSpace* space, cpBody* body, ofPolyline poly);
	void setup(cpSpace* space, cpBody* body, std::vector<ofVec2f>& points);

	void scale(float s) override;
	ofPath getAsPath() override;

	std::vector<ofVec2f> getPoints();
protected:
	void setup(cpSpace* space, cpBody* body, int nPoints, cpVect* pts);

	int numPoints;
	cpVect* points;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
