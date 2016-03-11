#include "ofxChipmunkLine.h"

namespace ofxChipmunk {

Line::Line(){

}

Line::Line(cpSpace *space, ofVec2f a, ofVec2f b, float radius, float mass){
    setup(space, a, b, radius, mass);
}

Line::Line(ShapeLine *src, float mass){
    cpFloat moment = cpMomentForSegment(mass, toChipmunk(src->getA()), toChipmunk(src->getB()), src->getRadius());
    DynamicBody::setup(cpShapeGetSpace(src->shape), mass, moment);
    ShapeLine::setup(src);
    cpSpaceRemoveShape(cpShapeGetSpace(shape), shape);
    cpSpaceAddShape(cpBodyGetSpace(body), shape);
    cpShapeSetBody(shape, body);
}

void Line::setup(cpSpace* space, ofVec2f a, ofVec2f b, float radius, float mass){
	DynamicBody::setup(space, mass, cpMomentForSegment(mass, toChipmunk(a), toChipmunk(b), radius));
    ShapeLine::setup(space, body, a, b, radius);
}

} // namespace ofxChipmunk
