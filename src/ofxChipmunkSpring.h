#ifndef OFXCHIPMUNK_SPRING_H
#define OFXCHIPMUNK_SPRING_H

#include "ofMain.h"
#include "ofxChipmunkBody.h"
#include "ofxChipmunkConstraint.h"

namespace ofxChipmunk {

class Spring: public Constraint{
public:
	using ForceFunction = std::function<float(Spring* spring, float distance)>;

    Spring();
	Spring(cpSpace* space, Body* a, Body* b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
	Spring(cpSpace* space, cpBody* a, cpBody* b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);

	void setup(cpSpace* space, Body* a, Body* b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);
	void setup(cpSpace* space, cpBody* a, cpBody* b, glm::vec2 anchorA, glm::vec2 anchorB, float distance, float stiffness=OFXCHIPMUNK_DEFAULT_STIFFNES, float damping=OFXCHIPMUNK_DEFAULT_DAMPING);

	float getStiffness();
	float getLength();
	void setLength(float length);
	void setStiffness(float stiffness);

	void setSpringForceFunction(ForceFunction f);

private:
	static cpFloat springForceFunc(cpConstraint* spring, cpFloat dist);

	ForceFunction forceFunction;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_SPRING_H
