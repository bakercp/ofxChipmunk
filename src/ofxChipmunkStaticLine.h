#ifndef OFXCHIPMUNK_STATICLINE_H
#define OFXCHIPMUNK_STATICLINE_H

#include "ofxChipmunkShape.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class StaticLine: public ShapeLine, public StaticBody{
public:
    StaticLine();
	StaticLine(cpSpace* space, glm::vec2 a, glm::vec2 b, float radius=0);

	void setup(cpSpace* space, glm::vec2 a, glm::vec2 b, float radius=0);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_STATICLINE_H
