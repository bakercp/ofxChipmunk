#ifndef OFXCHIPMUNK_STATICRECT_H
#define OFXCHIPMUNK_STATICRECT_H

#include "ofMain.h"
#include "ofxChipmunkShape.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class StaticRect: public Shape, public StaticBody{
public:
    StaticRect();
	StaticRect(cpSpace* space, ofRectangle bounds);

	void setup(cpSpace* space, ofRectangle bounds);

};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_STATICRECT_H
