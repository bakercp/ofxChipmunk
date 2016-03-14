#ifndef OFXCHIPMUNK_POLYGON_H
#define OFXCHIPMUNK_POLYGON_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

class Polygon: public DynamicBody, public ShapePolygon{
public:
    Polygon();
	Polygon(cpSpace* space, ofPolyline poly, float radius=0.f, float mass=1.f);
	Polygon(cpSpace* space, std::vector<ofVec2f>& points, float radius=0.f, float mass=1.f);
    Polygon(ShapePolygon* src, float mass=1.f);

	void setup(cpSpace* space, ofPolyline poly, float radius=0.f, float mass=1);
	void setup(cpSpace* space, std::vector<ofVec2f>& points, float radius=0.f, float mass=1);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_POLYGON_H
