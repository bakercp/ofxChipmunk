#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30);

	ofSetFrameRate(60);

	world.createFloor();

    circle = world.createCircle(20);
	circle->setPosition(ofVec2f(ofGetWidth()*.5, 10));

    rect = world.createRect(ofRectangle(0, 0, 200, 200), 100);
    rect->setPosition(ofVec2f(ofGetWidth()*.5, 50));
    rect->setRotation(ofDegToRad(48));
}

//--------------------------------------------------------------
void ofApp::update(){
	world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
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
