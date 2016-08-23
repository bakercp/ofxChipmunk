#ifndef OFXCHIPMUNK_WORLD_H
#define OFXCHIPMUNK_WORLD_H

#include "ofMain.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkCircle.h"
#include "ofxChipmunkComposite.h"
#include "ofxChipmunkLine.h"
#include "ofxChipmunkPivotJoint.h"
#include "ofxChipmunkPolygon.h"
#include "ofxChipmunkRect.h"
#include "ofxChipmunkSpring.h"
#include "ofxChipmunkStaticCircle.h"
#include "ofxChipmunkStaticLine.h"
#include "ofxChipmunkStaticRect.h"
#include "ofxChipmunkSimpleMotor.h"


namespace ofxChipmunk {

class World{
public:
    World();
    ~World();

    /*
    void runThreaded(const int runsPerUpdate);
    void threadLock();
    void threadUnlock();
    void threadStop();
    void waitForThread();
    void continueThread();
    */

    void update();
    void update(double timeStep);
    void draw();

    void setGravity(glm::vec2 g=glm::vec2(0, 100));
	glm::vec2 getGravity();
    void createFloor();
    void createWallLeft();
    void createWallRight();
    void createBounds();
    void setPicking(bool state=true);
    Body* getNearestBody(glm::vec2 pos, float radius=20.f);

	void setNumIterations(int i);
	int getNumIterations();

    //primitives
	shared_ptr<Circle> createCircle(float radius, float mass=1.f);
	shared_ptr<Rect> createRect(ofRectangle rect, float mass=1.f);
	shared_ptr<Line> createLine(glm::vec2 a, glm::vec2 b, float radius=0.f, float mass=1.f);
	shared_ptr<Polygon> createPoly(std::vector<glm::vec2>& points, float radius=0.f, float mass=1);
	shared_ptr<Polygon> createPoly(ofPolyline poly, float radius=1.f, float mass=1);
    shared_ptr<Composite> createComposite(Composite::Definition& definition);

    //kinematic primitives
    shared_ptr<KinematicBody> createKinematicBody(glm::vec2 position=glm::vec2(0,0));

    //static primitives
    shared_ptr<StaticBody> createStaticBody(glm::vec2 position=glm::vec2(0,0));
    shared_ptr<StaticLine> createStaticLine(glm::vec2 a, glm::vec2 b, float radius=0.f);
    shared_ptr<StaticRect> createStaticRect(ofRectangle rect);
    shared_ptr<StaticCircle> createStaticCircle(float radius);

    //constraints
    shared_ptr<Spring> createSpring(shared_ptr<Body> a, shared_ptr<Body> b, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
    shared_ptr<Spring> createSpring(Body* a, Body* b, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
    shared_ptr<Spring> createSpring(shared_ptr<Body> a, shared_ptr<Body> b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
    shared_ptr<Spring> createSpring(Body* a, Body* b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
    shared_ptr<PivotJoint> createPivotJoint(shared_ptr<Body> a, shared_ptr<Body> b, glm::vec2 anchorA = glm::vec2(0,0), glm::vec2 anchorB = glm::vec2(0,0));
    shared_ptr<PivotJoint> createPivotJoint(Body* a, Body* b, glm::vec2 anchorA = glm::vec2(0,0), glm::vec2 anchorB = glm::vec2(0,0));
	shared_ptr<SimpleMotor> createSimpleMotor(shared_ptr<Body> a, shared_ptr<Body> b, float rate=1);
	shared_ptr<SimpleMotor> createSimpleMotor(Body* a, Body* b, float rate=1);

    //helpers
    shared_ptr<DynamicBody> createBodyForShape(Shape* shape, float mass=1);


private:
    void onMouseDown(ofMouseEventArgs& args);
    void onMouseDrag(ofMouseEventArgs& args);
    void onMouseUp(ofMouseEventArgs& args);

    cpSpace* space;
    shared_ptr<StaticLine> floor;
    shared_ptr<StaticLine> wallLeft;
    shared_ptr<StaticLine> wallRight;
    bool bLowFPS;
    bool bPickingEnabled;
    shared_ptr<KinematicBody> mouseBody;
    shared_ptr<PivotJoint> mouseJoint;

    std::thread thread;
    std::mutex mutex;
    bool bKeepThreadRunning;
    bool bThreadWaiting;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_WORLD_H
