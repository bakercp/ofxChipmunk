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

void World::createWallLeft(){
	wallLeft = createStaticLine(ofVec2f(0, 0), ofVec2f(0, ofGetHeight()));
}

void World::createWallRight(){
	wallRight = createStaticLine(ofVec2f(ofGetWidth(), 0), ofVec2f(ofGetWidth(), ofGetHeight()));
}

void World::createBounds(){
	createFloor();
	createWallLeft();
	createWallRight();
}

shared_ptr<Circle> World::createCircle(float radius, float mass){
	return shared_ptr<Circle>(new Circle(space, radius, mass));
}

shared_ptr<Rect> World::createRect(ofRectangle rect, float mass){
	return shared_ptr<Rect>(new Rect(space, rect, mass));
}

shared_ptr<Polygon> World::createPoly(std::vector<ofVec2f>& points, float mass){
	return shared_ptr<Polygon>(new Polygon(space, points, mass));
}

shared_ptr<Polygon> World::createPoly(ofPolyline poly, float mass){
    return shared_ptr<Polygon>(new Polygon(space, poly, mass));
}

shared_ptr<Composite> World::createComposite(Composite::Definition &definition){
	return shared_ptr<Composite>(new Composite(space, definition));
}

shared_ptr<StaticLine> World::createStaticLine(ofVec2f a, ofVec2f b){
	return shared_ptr<StaticLine>(new StaticLine(space, a, b));
}

shared_ptr<StaticRect> World::createStaticRect(ofRectangle rect){
	return shared_ptr<StaticRect>(new StaticRect(space, rect));
}

shared_ptr<Spring> World::createSpring(shared_ptr<Body> a, shared_ptr<Body> b, float stiffness, float damping){
	return createSpring(a, b, ofVec2f(0, 0), ofVec2f(0, 0), a->getPosition().distance(b->getPosition()), stiffness, damping);
}

shared_ptr<Spring> World::createSpring(shared_ptr<Body> a, shared_ptr<Body> b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	return shared_ptr<Spring>(new Spring(space, a.get(), b.get(), anchorA, anchorB, distance, stiffness, damping));
}

void World::onClick(ofMouseEventArgs &args){

}

void World::onDrag(ofMouseEventArgs &args){

}

void World::onRelease(ofMouseEventArgs &args){

}


} // namespace ofxChipmunk
