#include "ofxChipmunkStaticRect.h"

namespace ofxChipmunk {

StaticRect::StaticRect(){

}

StaticRect::StaticRect(cpSpace *space, ofRectangle bounds){
	setup(space, bounds);
}

void StaticRect::setup(cpSpace *space, ofRectangle bounds){
	Shape::setup(space, cpBoxShapeNew2(cpSpaceGetStaticBody(space), toChipmunk(bounds), 0));
}

} // namespace ofxChipmunk
