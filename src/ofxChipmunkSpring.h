#ifndef OFXCHIPMUNK_SPRING_H
#define OFXCHIPMUNK_SPRING_H

#include "ofMain.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

class Spring: public Constraint{
public:
    Spring();

    void setup(cpSpace* space, Body* a, Body* b, ofVec2f anchorA, ofVec2f anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_SPRING_H
