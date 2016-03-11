#ifndef OFXCHIPMUNK_POLYGON_H
#define OFXCHIPMUNK_POLYGON_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

class Polygon: public DynamicBody, public ShapePolygon{
public:
    Polygon();
	Polygon(cpSpace* space, ofPolyline poly, float mass=1);
	Polygon(cpSpace* space, std::vector<ofVec2f>& points, float mass=1);
    Polygon(ShapePolygon* src, float mass=1.f);

    void setup(cpSpace* space, ofPolyline poly, float mass=1);
    void setup(cpSpace* space, std::vector<ofVec2f>& points, float mass=1);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_POLYGON_H
