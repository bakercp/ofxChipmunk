#ifndef OFXCHIPMUNK_STATICLINE_H
#define OFXCHIPMUNK_STATICLINE_H

#include "ofxChipmunkShape.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class StaticLine: public Shape{
public:
    StaticLine();
	StaticLine(cpSpace* space, ofVec2f a, ofVec2f b);

    void setup(cpSpace* space, ofVec2f a, ofVec2f b);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_STATICLINE_H
