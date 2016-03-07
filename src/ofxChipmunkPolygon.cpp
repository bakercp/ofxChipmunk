#include "ofxChipmunkPolygon.h"

namespace ofxChipmunk {

Polygon::Polygon(){

}

Polygon::Polygon(cpSpace *space, ofPolyline poly, float mass){
	setup(space, poly, mass);
}

Polygon::Polygon(cpSpace *space, std::vector<ofVec2f> &points, float mass){
	setup(space, points, mass);
}

void Polygon::setup(cpSpace *space, ofPolyline poly, float mass){
	std::vector<ofVec2f> vecs;
	for(auto& p: poly){
		vecs.push_back(p);
	}
	setup(space, vecs, mass);
}

void Polygon::setup(cpSpace *space, std::vector<ofVec2f> &points, float mass){
	cpVect verts[points.size()];
	for(size_t i=0; i<points.size(); i++){
		verts[i] = toChipmunk(points[i]);
	}

	cpFloat moment = cpMomentForPoly(mass, points.size(), verts, cpvzero, 0.0);
	Body::setup(space, mass, moment);
    ShapePolygon::setup(space, body, points.size(), verts);
}

} // namespace ofxChipmunk
