#ifndef OFXCHIPMUNK_STATICCIRCLE_H
#define OFXCHIPMUNK_STATICCIRCLE_H

#include "ofxChipmunkShape.h"
#include "ofxChipmunkBody.h"


namespace ofxChipmunk {

class StaticCircle: public StaticBody, public ShapeCircle{
public:
    StaticCircle();

    StaticCircle(cpSpace* space, float radius);

    void setup(cpSpace* space, float radius);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_STATICCIRCLE_H
