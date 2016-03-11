#ifndef OFXCHIPMUNK_LINE_H
#define OFXCHIPMUNK_LINE_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

class Line: public DynamicBody, public ShapeLine{
public:
    Line();
    Line(cpSpace* space, ofVec2f a, ofVec2f b, float radius=0, float mass=1);

    void setup(cpSpace* space, ofVec2f a, ofVec2f b, float radius=0, float mass=1);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_LINE_H
