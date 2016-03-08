#include "ofxChipmunkStaticCircle.h"

namespace ofxChipmunk {

StaticCircle::StaticCircle(){

}

StaticCircle::StaticCircle(cpSpace *space, float radius){
    setup(space, radius);
}

void StaticCircle::setup(cpSpace *space, float radius){
    StaticBody::setup(space);
	ShapeCircle::setup(space, body, radius);
}

} // namespace ofxChipmunk
