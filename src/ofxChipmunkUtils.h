#ifndef OFXCHIPMUNK_UTILS_H
#define OFXCHIPMUNK_UTILS_H

#include "ofMain.h"
#include <chipmunk.h>

namespace ofxChipmunk {

//converting
cpVect toChipmunk(ofVec2f v);
ofVec2f toOf(cpVect v);

cpBB toChipmunk(ofRectangle rect);
ofRectangle toOf(cpBB rect);

//drawing
void drawSpace(cpSpace* space);
void drawCircle(cpVect p, cpFloat a, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data);
void drawFatSegment(cpVect a, cpVect b, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawPolygon(int count, const cpVect *verts, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data);
void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data);

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_UTILS_H
