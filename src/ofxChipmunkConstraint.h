#ifndef OFXCHIPMUNK_CONSTRAINT_H
#define OFXCHIPMUNK_CONSTRAINT_H

#include "ofMain.h"
#include <chipmunk.h>

namespace ofxChipmunk {

class Constraint{
public:

	void setMaxForce(double force);
	void setErrorBias(double bias);

	cpConstraint* constraint;

protected:
    Constraint();
	~Constraint();

	void setup(cpSpace* space, cpConstraint* constraint);
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_CONSTRAINT_H
