#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30);

	ofSetFrameRate(60);

	world.createBounds();

	//
    circle = world.createCircle(20);
	circle->setPosition(ofVec2f(ofGetWidth()*.5, 40));

	//
	rect = world.createRect(ofRectangle(0, 0, 150, 200), 100);
	rect->setPosition(ofVec2f(ofGetWidth()*.5, 200));
	rect->setRotation(ofDegToRad(60));

	//
	ofPolyline polyline;
	for(unsigned i=0; i<17; i++){
		float angle = ofMap(i, 0, 17, 0, TWO_PI);
		float r = ofRandom(15, 100);
		polyline.addVertex(cosf(angle)*r, sinf(angle)*r);
	}

	//create a polygon with the polyline, will automatically be converted to a concave shape
	poly = world.createPoly(polyline);
	poly->setPosition(ofVec2f(ofGetWidth()*.4, 0));

	//to create a convex shape, create a Composite and add the polyline. The composite will automatically split it into concave subshapes
	Composite::Definition def;
	def.addConvexPolygon(polyline);
	//def.addCircle(50, ofVec2f(10, 10), 1);
	//def.addCircle(50, ofVec2f(-50, -50));
	//def.addRect(ofRectangle(-10, -10, 100, 100));
	composite = world.createComposite(def);
	composite->setPosition(ofVec2f(ofGetWidth()*.53, 100));

	//
	spring = world.createSpring(circle, rect);
	spring = world.createSpring(circle, poly);
}

//--------------------------------------------------------------
void ofApp::update(){
	//circle->setRadius(circle->getRadius()+.3);

	world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//debug drawing may be slow...
	world.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
