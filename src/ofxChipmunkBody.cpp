#include "ofxChipmunkBody.h"

namespace ofxChipmunk {

Body::Body():body(nullptr){

}

Body::~Body(){
	cpBodyFree(body);
}

void Body::setup(cpSpace* space,float mass, cpFloat moment){
	body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
}

bool Body::isSleeping(){
	return cpBodyIsSleeping(body);
}

ofVec2f Body::getPosition(){
	return toOf(cpBodyGetPosition(body));
}

void Body::setPosition(ofVec2f pos){
    cpBodySetPosition(body, toChipmunk(pos));
}

void Body::setRotation(float radians){
    cpBodySetAngle(body, radians);
}

}// namespace ofxChimpunk
