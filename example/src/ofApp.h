#pragma once

#include "ofMain.h"
#include "ofxChipmunk.h"

using namespace ofxChipmunk;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	World world;
	shared_ptr<Circle> circle;
	shared_ptr<Rect> rect;
	shared_ptr<Polygon> poly;
	shared_ptr<Spring> spring1;
	shared_ptr<Spring> spring2;
	shared_ptr<Spring> spring3;
	shared_ptr<Composite> composite;
	shared_ptr<StaticBody> anchor;
    vector<shared_ptr<DynamicBody>> parts;
};
