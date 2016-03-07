#include "ofxChipmunkRect.h"

namespace ofxChipmunk {

Rect::Rect(){
}

Rect::Rect(cpSpace *space, ofRectangle bounds, float mass){
	setup(space, bounds, mass);
}

void Rect::setup(cpSpace *space, ofRectangle bounds, float mass){
	cpFloat moment = cpMomentForBox2(mass, toChipmunk(bounds));
	Body::setup(space, mass, moment);
    ShapeRect::setup(space, body, bounds);
    setPosition(bounds.getPosition());
}

} // namespace ofxChipmunk
