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
	std::vector<cpVect> verts = toChipmunk(points);
	cpFloat moment = cpMomentForPoly(mass, points.size(), verts.data(), cpvzero, 0.0);
	DynamicBody::setup(space, mass, moment);
	ShapePolygon::setup(space, body, points.size(), verts.data());
}

} // namespace ofxChipmunk
