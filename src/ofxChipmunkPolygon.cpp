#include "ofxChipmunkPolygon.h"

namespace ofxChipmunk {

Polygon::Polygon(){

}

Polygon::Polygon(cpSpace *space, ofPolyline poly, float radius, float mass){
	setup(space, poly, radius, mass);
}

Polygon::Polygon(cpSpace *space, std::vector<glm::vec2> &points, float radius, float mass){
	setup(space, points, radius, mass);
}

Polygon::Polygon(ShapePolygon *src, float mass){
    std::vector<glm::vec2> ofVerts = src->getPoints();
    std::vector<cpVect> verts = toChipmunk(ofVerts);
	cpFloat moment = cpMomentForPoly(mass, verts.size(), verts.data(), cpvzero, cpPolyShapeGetRadius(src->shape));
    DynamicBody::setup(cpShapeGetSpace(src->shape), mass, moment);
    cpSpaceRemoveShape(cpShapeGetSpace(src->shape), src->shape);
    ShapePolygon::setup(src);
    cpShapeSetBody(shape, body);
    cpSpaceAddShape(cpBodyGetSpace(body), shape);
}

void Polygon::setup(cpSpace *space, ofPolyline poly, float radius, float mass){
	std::vector<glm::vec2> vecs;
	for(auto& p: poly){
		vecs.push_back(glm::vec2(p.x, p.y));
	}
	setup(space, vecs, radius, mass);
}

void Polygon::setup(cpSpace *space, std::vector<glm::vec2> &points, float radius, float mass){
	std::vector<cpVect> verts = toChipmunk(points);
	cpFloat moment = cpMomentForPoly(mass, points.size(), verts.data(), cpvzero, radius);
	DynamicBody::setup(space, mass, moment);
	ShapePolygon::setup(space, body, points.size(), verts.data(), radius);
}

} // namespace ofxChipmunk
