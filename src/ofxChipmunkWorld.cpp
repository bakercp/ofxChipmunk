#include "ofxChipmunkWorld.h"

namespace ofxChipmunk {


World::World(){
	space = cpSpaceNew();
	setGravity();
}

World::~World(){
	cpSpaceFree(space);
}

void World::update(){
    if(ofGetFrameNum() < 10)
        return;

	int targetFPS = ofGetTargetFrameRate();
	if(targetFPS == 0){
		ofLogWarning("ofxChipmunk") << "no fixed framerate set, it is recommended to use ofSetFrameRate()";
		targetFPS = 60;
	}

	int curFPS = ofGetFrameRate();
	if(curFPS < targetFPS*.95 && ofGetFrameNum() > 60){
		ofLogWarning("ofxChipmunk") << "current framerate (" << curFPS << ") is bellow target framerate (" << targetFPS << "), physics may behave strangely";
	}

    cpSpaceStep(space, 1.f/float(targetFPS));
}

void World::draw(){
	drawSpace(space);
}

void World::setGravity(ofVec2f g){
	cpSpaceSetGravity(space, toChipmunk(g));
}

void World::createFloor(){
    floor = createStaticLine(ofVec2f(0, ofGetHeight()), ofVec2f(ofGetWidth(), ofGetHeight()));
}

shared_ptr<Circle> World::createCircle(float radius, float mass){
	return shared_ptr<Circle>(new Circle(space, radius, mass));
}

shared_ptr<Rect> World::createRect(ofRectangle rect, float mass){
	return shared_ptr<Rect>(new Rect(space, rect, mass));
}

shared_ptr<StaticLine> World::createStaticLine(ofVec2f a, ofVec2f b){
	return shared_ptr<StaticLine>(new StaticLine(space, a, b));
}


} // namespace ofxChipmunk
