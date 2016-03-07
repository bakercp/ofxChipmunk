#ifndef OFXCHIMPUNK_COMPOSITE_H
#define OFXCHIMPUNK_COMPOSITE_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

class Composite: public Body{
public:
    Composite();

    void setup(cpSpace* space);

    void addCircle(ofVec2f offset, float radius, float mass=1);
    void addRect(ofRectangle r, float mass=1);
    void addPolygon(ofPolyline p, float mass=1);

    void build();

private:
    void add(Shape* shape);


    class Temp{
    public:
        cpFloat mass;
        cpFloat moment;
    };

    class TempCircle: public Temp{
    public:
        float radius;
        ofVec2f offset;
    };

    class TempRect: public Temp{
    public:
        ofRectangle rect;
    };

    class TempPoly: public Temp{
    public:
        cpVect* vects;
        int numVects;
    };

    std::vector<shared_ptr<Shape>> shapes;

    std::vector<TempCircle> tmpCircles;
    std::vector<TempRect> tmpRects;
    std::vector<TempPoly> tmpPolys;

    cpSpace* space;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_COMPOSITE_H
