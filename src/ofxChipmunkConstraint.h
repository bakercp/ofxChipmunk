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

	void disable();
	void enable();

protected:
    Constraint();
	~Constraint();

	void setup(cpSpace* space, cpConstraint* constraint);

	cpSpace* tmpSpace;
};

} // namespace ofxChipmunk

#endif // OFXCHIPMUNK_CONSTRAINT_H
