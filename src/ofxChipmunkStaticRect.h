#ifndef OFXCHIPMUNK_STATICRECT_H
#define OFXCHIPMUNK_STATICRECT_H

#include "ofMain.h"
#include "ofxChipmunkShape.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class StaticRect: public ShapeRect, public StaticBody{
public:
    StaticRect();
    StaticRect(cpSpace* space, ofRectangle bounds, float radius=1.f);

    void setup(cpSpace* space, ofRectangle bounds, float radius=1.f);

};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_STATICRECT_H
