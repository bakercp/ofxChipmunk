#include "ofApp.h"

enum CollisionGroups{
	NONE,
	DEFAULT
};

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(30);

	ofSetFrameRate(60);

	world.createBounds();
	world.setPicking();

	//
	circle = world.createCircle(20);
	circle->setPosition(glm::vec2(ofGetWidth()*.5, 40));



	//
	rect = world.createRect(ofRectangle(0, 0, 150, 200), 100);
	rect->setPosition(glm::vec2(ofGetWidth()*.5, 200));
	rect->setRotation(ofDegToRad(60));



	//
	ofPolyline polyline;
	for(unsigned i=0; i<17; i++){
		float angle = ofMap(i, 0, 17, 0, TWO_PI);
		float r = ofRandom(15, 100);
		polyline.addVertex(cosf(angle)*r, sinf(angle)*r);
	}

	//NOTE: create a polygon with the polyline, will automatically be converted to a convex shape (outer hull)
	poly = world.createPoly(polyline);
	poly->setPosition(glm::vec2(ofGetWidth()*.4, 0));



	//poly->setCollisionFilter(CollisionGroups::NONE, ~CollisionGroups::DEFAULT, ~CollisionGroups::DEFAULT);

	//NOTE: to create a concave shape, create a Composite and add the polyline. The composite will automatically split it into convex subshapes
	Composite::Definition def;
	def.addConcavePolygon(polyline);
	//def.addCircle(50, glm::vec2(10, 10));
	//def.addCircle(50, glm::vec2(-50, -50));
	//def.addRect(ofRectangle(-10, -10, 100, 100));
	composite = world.createComposite(def);
	composite->setPosition(glm::vec2(ofGetWidth()*.53, 100));

	composite->setScale(2);

	//anchor
	anchor = world.createStaticBody();
	anchor->setPosition(glm::vec2(ofGetWidth()*.7, 40));

	//
	spring1 = world.createSpring(circle, rect);
	spring2 = world.createSpring(circle, poly);
	spring2 = world.createSpring(anchor, composite);

	// to disable collision between circle and poly (same groups do not collide)
	//circle->collisionSetGroup(3);
	//poly->collisionSetGroup(3);

}

//--------------------------------------------------------------
void ofApp::update(){

	//composite->setScale(1.2);

	//not needed when running threaded

	world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//debug drawing may be slow...
	world.draw();

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), glm::vec2(20, 20));

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == ' '){
        parts = composite->breakApart();
		composite.reset();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
