#include "ofxChipmunkBody.h"

namespace ofxChipmunk {

Body::Body():body(nullptr){

}

Body::~Body(){
	if(body){
		cpSpaceRemoveBody(cpBodyGetSpace(body), body);
		cpBodyFree(body);
	}
}

void Body::setup(cpSpace *space, cpBody *b){
	body = cpSpaceAddBody(space, b);
	cpBodySetUserData(body, this);
}

ofVec2f ofxChipmunk::Body::getPosition(){
	return toOf(cpBodyGetPosition(body));
}

void Body::setPosition(ofVec2f pos){
	cpBodySetPosition(body, toChipmunk(pos));
}

float Body::getRotation(){
	return cpBodyGetAngle(body);
}

void Body::setRotation(float radians){
	cpBodySetAngle(body, radians);
}

bool Body::isSleeping(){
	return cpBodyIsSleeping(body);
}

////////////////////////////////////////////////////
DynamicBody::DynamicBody(){

}

DynamicBody::~DynamicBody(){

}

void DynamicBody::setup(cpSpace* space,float mass, cpFloat moment){
	Body::setup(space, cpBodyNew(mass, moment));
}

/////////////////////////////////////////////////////////////

StaticBody::StaticBody(){

}

StaticBody::StaticBody(cpSpace *space){
	setup(space);
}

void ofxChipmunk::StaticBody::setup(cpSpace *space){
	Body::setup(space, cpBodyNewStatic());
}

////////////////////////////////////////////////////////
KinematicBody::KinematicBody(){
}

KinematicBody::KinematicBody(cpSpace *space){
	setup(space);
}

void KinematicBody::setup(cpSpace *space){
	Body::setup(space, cpBodyNewKinematic());
}


}// namespace ofxChimpunk
