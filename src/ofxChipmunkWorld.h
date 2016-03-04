#ifndef OFXCHIPMUNK_WORLD_H
#define OFXCHIPMUNK_WORLD_H

#include "ofMain.h"
#include "ofxChipmunkUtils.h"
#include "ofxChipmunkCircle.h"
#include "ofxChipmunkStaticLine.h"
#include "ofxChipmunkRect.h"

namespace ofxChipmunk {

class World{
public:
	World();
	~World();

	void update();
	void draw();

	void setGravity(ofVec2f g=ofVec2f(0, 100));
	void createFloor();

	shared_ptr<Circle> createCircle(float radius, float mass=1);
	shared_ptr<Rect> createRect(ofRectangle rect, float mass=1);
	shared_ptr<StaticLine> createStaticLine(ofVec2f a, ofVec2f b);

private:
    cpSpace* space;
	shared_ptr<StaticLine> floor;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_WORLD_H
