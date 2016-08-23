#ifndef OFXCHIPMUNK_LINE_H
#define OFXCHIPMUNK_LINE_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"

namespace ofxChipmunk {

class Line: public DynamicBody, public ShapeLine{
public:
    Line();
    Line(cpSpace* space, glm::vec2 a, glm::vec2 b, float radius=0, float mass=1);
    Line(ShapeLine* src, float mass=1.f);

    void setup(cpSpace* space, glm::vec2 a, glm::vec2 b, float radius=0, float mass=1);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_LINE_H
