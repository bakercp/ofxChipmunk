#include "ofxChipmunkRect.h"

namespace ofxChipmunk {

Rect::Rect(){
}

Rect::Rect(cpSpace *space, ofRectangle bounds, float mass){
	setup(space, bounds, mass);
}

void Rect::setup(cpSpace *space, ofRectangle bounds, float mass){
	cpFloat moment = cpMomentForBox2(mass, toChipmunk(bounds));
	DynamicBody::setup(space, mass, moment);
    ShapeRect::setup(space, body, bounds);
	auto p = bounds.getPosition();
	setPosition(glm::vec2(p.x, p.y));
}

} // namespace ofxChipmunk
