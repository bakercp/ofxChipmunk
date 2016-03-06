#ifndef OFXCHIPMUNK_WORLD_H
#define OFXCHIPMUNK_WORLD_H

#include "ofMain.h"
#include "ofxChipmunkUtils.h"
#include "ofxChipmunkCircle.h"
#include "ofxChipmunkStaticLine.h"
#include "ofxChipmunkRect.h"
#include "ofxChipmunkStaticRect.h"

namespace ofxChipmunk {

class World{
public:
	World();
	~World();

	void update();
	void draw();

	void setGravity(ofVec2f g=ofVec2f(0, 100));
	void createFloor();
	void createWallLeft();
	void createWallRight();
	void createBounds();

	shared_ptr<Circle> createCircle(float radius, float mass=1);
	shared_ptr<Rect> createRect(ofRectangle rect, float mass=1);
	shared_ptr<StaticLine> createStaticLine(ofVec2f a, ofVec2f b);
	shared_ptr<StaticRect> createStaticRect(ofRectangle rect);

private:
    cpSpace* space;
	shared_ptr<StaticLine> floor;
	shared_ptr<StaticLine> wallLeft;
	shared_ptr<StaticLine> wallRight;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_WORLD_H
