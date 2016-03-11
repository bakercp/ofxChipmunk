#include "ofxChipmunkStaticLine.h"

namespace ofxChipmunk {

StaticLine::StaticLine(){

}

StaticLine::StaticLine(cpSpace *space, ofVec2f a, ofVec2f b, float radius){
	setup(space, a, b, radius);
}

void StaticLine::setup(cpSpace *space, ofVec2f a, ofVec2f b, float radius){
	StaticBody::setup(space);
	//Shape::setup(space, cpSegmentShapeNew(body, toChipmunk(a), toChipmunk(b), 1.f));
	//setFriction(.7);
	ShapeLine::setup(space, body, a, b, radius);
}

} // namespace ofxChipmunk
