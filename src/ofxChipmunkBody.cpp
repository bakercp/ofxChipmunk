#include "ofxChipmunkBody.h"

namespace ofxChipmunk {

BaseBody::BaseBody():body(nullptr){

}

BaseBody::~BaseBody(){
	if(body){
		cpSpaceRemoveBody(cpBodyGetSpace(body), body);
		cpBodyFree(body);
	}
}

void BaseBody::setup(cpSpace *space, cpBody *b){
	body = cpSpaceAddBody(space, b);
}

ofVec2f ofxChipmunk::BaseBody::getPosition(){
	return toOf(cpBodyGetPosition(body));
}

void BaseBody::setPosition(ofVec2f pos){
	cpBodySetPosition(body, toChipmunk(pos));
}

float BaseBody::getRotation(){
	return cpBodyGetAngle(body);
}

void BaseBody::setRotation(float radians){
	cpBodySetAngle(body, radians);
}

bool BaseBody::isSleeping(){
	return cpBodyIsSleeping(body);
}

////////////////////////////////////////////////////
Body::Body(){

}

Body::~Body(){

}

void Body::setup(cpSpace* space,float mass, cpFloat moment){
	BaseBody::setup(space, cpBodyNew(mass, moment));
}

/////////////////////////////////////////////////////////////

StaticBody::StaticBody(){

}

StaticBody::StaticBody(cpSpace *space){
	setup(space);
}

void ofxChipmunk::StaticBody::setup(cpSpace *space){
	body = cpBodyNewStatic();
	BaseBody::setup(space, body);
}


}// namespace ofxChimpunk
