#include "ofxChipmunkStaticRect.h"

namespace ofxChipmunk {

StaticRect::StaticRect(){

}

StaticRect::StaticRect(cpSpace *space, ofRectangle bounds, float radius){
	setup(space, bounds);
}

void StaticRect::setup(cpSpace *space, ofRectangle bounds, float radius){
	StaticBody::setup(space);
    ShapeRect::setup(space, body, bounds, radius);
}

} // namespace ofxChipmunk
