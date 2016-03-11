#include "ofxChipmunkWorld.h"

namespace ofxChipmunk {


World::World(){
	space = cpSpaceNew();
	setGravity();
	bLowFPS = false;

	ofAddListener(ofEvents().mousePressed, this, &World::onMouseDown);
	ofAddListener(ofEvents().mouseDragged, this, &World::onMouseDrag);
	ofAddListener(ofEvents().mouseReleased, this, &World::onMouseUp);
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
		if(!bLowFPS)
			ofLogWarning("ofxChipmunk") << "current framerate (" << curFPS << ") is bellow target framerate (" << targetFPS << "), physics may behave strangely";
		bLowFPS = true;
	}else{
		bLowFPS = false;
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

void World::setPicking(bool state){
	bPickingEnabled = state;
}

Body* World::getNearestBody(ofVec2f pos, float radius){
	cpShape* shape = cpSpacePointQueryNearest(space, toChipmunk(pos), radius, CP_SHAPE_FILTER_ALL, NULL);
	if(!shape)
		return nullptr;
	return (Body*)cpBodyGetUserData(cpShapeGetBody(shape));
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

shared_ptr<KinematicBody> World::createKinematicBody(ofVec2f position){
	KinematicBody* body = new KinematicBody(space);
	body->setPosition(position);
	return shared_ptr<KinematicBody>(body);
}

shared_ptr<StaticBody> World::createStaticBody(ofVec2f position){
	StaticBody* body = new StaticBody(space);
	body->setPosition(position);
	return shared_ptr<StaticBody>(body);
}

shared_ptr<StaticLine> World::createStaticLine(ofVec2f a, ofVec2f b){
	return shared_ptr<StaticLine>(new StaticLine(space, a, b));
}

shared_ptr<StaticRect> World::createStaticRect(ofRectangle rect){
	return shared_ptr<StaticRect>(new StaticRect(space, rect));
}

shared_ptr<StaticCircle> World::createStaticCircle(float radius){
	return shared_ptr<StaticCircle>(new StaticCircle(space, radius));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SPRINGS


shared_ptr<Spring> World::createSpring(shared_ptr<Body> a, shared_ptr<Body> b, float stiffness, float damping){
	return createSpring(a, b, ofVec2f(0, 0), ofVec2f(0, 0), a->getPosition().distance(b->getPosition()), stiffness, damping);
}

shared_ptr<Spring> World::createSpring(Body *a, Body *b, float stiffness, float damping){
	return createSpring(a, b, ofVec2f(0, 0), ofVec2f(0, 0), a->getPosition().distance(b->getPosition()), stiffness, damping);
}

shared_ptr<Spring> World::createSpring(shared_ptr<Body> a, shared_ptr<Body> b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	return createSpring(a.get(), b.get(), anchorA, anchorB, distance, stiffness, damping);
}

shared_ptr<Spring> World::createSpring(Body *a, Body *b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness, float damping){
	return shared_ptr<Spring>(new Spring(space, a, b, anchorA, anchorB, distance, stiffness, damping));
}

shared_ptr<PivotJoint> World::createPivotJoint(shared_ptr<Body> a, shared_ptr<Body> b, ofVec2f anchorA, ofVec2f anchorB){
	return createPivotJoint(a.get(), b.get(), anchorA, anchorB);
}

shared_ptr<PivotJoint> World::createPivotJoint(Body *a, Body *b, ofVec2f anchorA, ofVec2f anchorB){
	return shared_ptr<PivotJoint>(new PivotJoint(space, a, b, anchorA, anchorB));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void World::onMouseDown(ofMouseEventArgs &args){
	if(!bPickingEnabled) return;
	Body* body = getNearestBody(args);
	if(!body)
		return;

	if(!mouseBody)
		mouseBody = createKinematicBody(args);

	mouseJoint = createPivotJoint(mouseBody.get(), body);
	mouseJoint->setMaxForce(50000.0);
	mouseJoint->setErrorBias(cpfpow(1.0f - 0.15f, ofGetFrameRate()==0?60.f:ofGetFrameRate()));
}

void World::onMouseDrag(ofMouseEventArgs &args){
	if(!bPickingEnabled) return;

	if(mouseJoint)
		mouseBody->setPosition(args);
}

void World::onMouseUp(ofMouseEventArgs &args){
	if(!bPickingEnabled) return;

	if(mouseJoint)
		mouseJoint.reset();
}


} // namespace ofxChipmunk
