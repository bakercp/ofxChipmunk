#include "ofxChipmunkStaticLine.h"

namespace ofxChipmunk {

StaticLine::StaticLine(){

}

StaticLine::StaticLine(cpSpace *space, ofVec2f a, ofVec2f b){
	setup(space, a, b);
}

void StaticLine::setup(cpSpace *space, ofVec2f a, ofVec2f b){
	StaticBody::setup(space);
	Shape::setup(space, cpSegmentShapeNew(body, toChipmunk(a), toChipmunk(b), 1.f));
	setFriction(.7);
}

} // namespace ofxChipmunk
