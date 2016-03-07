#ifndef OFXCHIPMUNK_UTILS_H
#define OFXCHIPMUNK_UTILS_H

#include "ofMain.h"
#include <chipmunk.h>

#define OFXCHIPMUNK_DEFAULT_STIFFNES 5.f
#define OFXCHIPMUNK_DEFAULT_DAMPING .3f
#define OFXCHIPMUNK_DEFAULT_FRICTION .7f
#define OFXCHIPMUNK_DEFAULT_ELASTICITY .1f

namespace ofxChipmunk {

//converting
cpVect toChipmunk(ofVec2f v);
ofVec2f toOf(cpVect v);

cpBB toChipmunk(ofRectangle rect);
ofRectangle toOf(cpBB rect);

std::vector<cpVect> toChipmunk(std::vector<ofVec2f>& points);

//drawing
void drawSpace(cpSpace* space);
void drawCircle(cpVect p, cpFloat a, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data);
void drawFatSegment(cpVect a, cpVect b, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawPolygon(int count, const cpVect *verts, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data);

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_UTILS_H
