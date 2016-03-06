#include "ofxChipmunkStaticLine.h"

namespace ofxChipmunk {

StaticLine::StaticLine(){

}

StaticLine::StaticLine(cpSpace *space, ofVec2f a, ofVec2f b){
	setup(space, a, b);
}

void StaticLine::setup(cpSpace *space, ofVec2f a, ofVec2f b){
	Shape::setup(space, cpSegmentShapeNew(cpSpaceGetStaticBody(space), toChipmunk(a), toChipmunk(b), 0.f));
	setFriction(.7);
}

} // namespace ofxChipmunk
