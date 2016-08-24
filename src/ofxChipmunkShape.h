#ifndef OFXCHIMPUNK_SHAPE_H
#define OFXCHIMPUNK_SHAPE_H

#include "ofMain.h"
#include <chipmunk.h>
#include "chipmunk_unsafe.h"


namespace ofxChipmunk {


class Shape {
public:

    enum Type{
        Circle,
        Polygon,
        Line,
        Rectangle
    };

    Shape();
    ~Shape();

    void setup(cpSpace* space, cpShape* shape);

    void setElasticity(float);
    void setFriction(float friction);

    //very unsafe function
    virtual void scale(float s){ofLogNotice("ofxChipmunk") << "Scale not implemented for this shape";};

	virtual ofPath getAsPath(){ofLogNotice("ofxChipmunk") << "GetAsPath not implemented for this shape";return ofPath();};

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
    virtual Shape::Type getType()=0;

    void setCollisionType(int typeId);

    cpShape* shape;
};

class ShapeCircle: public Shape{
public:
    ShapeCircle();
    ShapeCircle(cpSpace* space, cpBody* body, float radius, glm::vec2 offset = glm::vec2(0, 0));
    void setup(cpSpace* space, cpBody* body, float radius, glm::vec2 offset = glm::vec2(0, 0));
    void setup(ShapeCircle* shape);

    void setRadius(float r);
    float getRadius();

    void setOffset(glm::vec2 off);
    glm::vec2 getOffset();

    void scale(float s) override;
    ofPath getAsPath() override;
    Shape::Type getType() override;
protected:
    float radiusInitial;
    glm::vec2 offsetInitial;
};

class ShapeRect: public Shape{
public:
    ShapeRect();
    ShapeRect(cpSpace* space, cpBody* body, ofRectangle bounds, float radius=0);
	void scale(float s) override;
	void scale(glm::vec2 scale);
	void scale(float sx, float sy);
	glm::vec2 getScale();
	void setup(cpSpace* space, cpBody* body, ofRectangle bounds, float radius=0);
    Shape::Type getType() override;

protected:

	int numPoints;
	cpVect* points;
	float curScaleX, curScaleY;
};

class ShapeLine: public Shape{
public:
    ShapeLine();
    ShapeLine(cpSpace* space, cpBody* body, glm::vec2 a, glm::vec2 b, float radius=0);
    void setup(cpSpace* space, cpBody* body, glm::vec2 a, glm::vec2 b, float radius=0);
    void setup(ShapeLine* src);
    glm::vec2 getA();
    glm::vec2 getB();
    float getRadius();
    void scale(float s) override;
    ofPath getAsPath() override;
    Shape::Type getType() override;

protected:
    glm::vec2 aInitial, bInitial;
    float radiusInitial;

};

class ShapePolygon: public Shape{
public:
    ShapePolygon();
    ~ShapePolygon();
	ShapePolygon(cpSpace* space, cpBody* body, ofPolyline poly, float radius=0.f);
	ShapePolygon(cpSpace* space, cpBody* body, std::vector<glm::vec2>& points, float radius=0.f);

	void setup(cpSpace* space, cpBody* body, ofPolyline poly, float radius=0.f);
	void setup(cpSpace* space, cpBody* body, std::vector<glm::vec2>& points, float radius=0.f);
    void setup(ShapePolygon* src);

	void setRadius(float radius);
    void scale(float s) override;
    ofPath getAsPath() override;
    Shape::Type getType() override;

    std::vector<glm::vec2> getPoints();
	glm::vec2 getCenter();
	void setOffset(glm::vec2 off);
protected:
	void setup(cpSpace* space, cpBody* body, int nPoints, cpVect* pts, float radius=0.f);

    int numPoints;
    cpVect* points;
	float curScale;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_SHAPE_H
