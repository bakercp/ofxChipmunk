#ifndef OFXCHIPMUNK_WORLD_H
#define OFXCHIPMUNK_WORLD_H

#include "ofMain.h"
#include "ofxChipmunkUtils.h"
#include "ofxChipmunkCircle.h"
#include "ofxChipmunkStaticLine.h"
#include "ofxChipmunkRect.h"
#include "ofxChipmunkStaticRect.h"
#include "ofxChipmunkSpring.h"
#include "ofxChipmunkPolygon.h"
#include "ofxChipmunkComposite.h"
#include "ofxChipmunkStaticCircle.h"

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

	//primitives
	shared_ptr<Circle> createCircle(float radius, float mass=1);
	shared_ptr<Rect> createRect(ofRectangle rect, float mass=1);
	shared_ptr<Polygon> createPoly(std::vector<ofVec2f>& points, float mass=1);
	shared_ptr<Polygon> createPoly(ofPolyline poly, float mass=1);
	shared_ptr<Composite> createComposite(Composite::Definition& definition);

	//static primitives
	shared_ptr<StaticBody> createStaticBody();
	shared_ptr<StaticLine> createStaticLine(ofVec2f a, ofVec2f b);
	shared_ptr<StaticRect> createStaticRect(ofRectangle rect);
	shared_ptr<StaticCircle> createStaticCircle(float radius);

	//constraints
	shared_ptr<Spring> createSpring(shared_ptr<BaseBody> a, shared_ptr<BaseBody> b, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
	shared_ptr<Spring> createSpring(shared_ptr<BaseBody> a, shared_ptr<BaseBody> b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);

private:
	void onClick(ofMouseEventArgs& args);
	void onDrag(ofMouseEventArgs& args);
	void onRelease(ofMouseEventArgs& args);

    cpSpace* space;
	shared_ptr<StaticLine> floor;
	shared_ptr<StaticLine> wallLeft;
	shared_ptr<StaticLine> wallRight;
	bool lowFPS;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_WORLD_H
