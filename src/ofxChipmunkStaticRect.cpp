#include "ofxChipmunkStaticRect.h"

namespace ofxChipmunk {

StaticRect::StaticRect(){

}

StaticRect::StaticRect(cpSpace *space, ofRectangle bounds){
	setup(space, bounds);
}

void StaticRect::setup(cpSpace *space, ofRectangle bounds){
	StaticBody::setup(space);
	Shape::setup(space, cpBoxShapeNew2(body, toChipmunk(bounds), 0));
}

} // namespace ofxChipmunk
