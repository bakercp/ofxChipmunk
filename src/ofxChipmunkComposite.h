#ifndef OFXCHIMPUNK_COMPOSITE_H
#define OFXCHIMPUNK_COMPOSITE_H

#include "ofxChipmunkBody.h"
#include "ofxChipmunkShape.h"
#include "ofxChipmunkCircle.h"
#include "ofxChipmunkRect.h"
#include "ofxChipmunkPolygon.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

class Composite: public DynamicBody{
public:
	class Definition{
	private:
		class ShapeDefinition{
		public:
			cpFloat mass;
			cpFloat moment;
			cpFloat elasticity;
			cpFloat friction;

			virtual Shape* create(cpSpace* space, cpBody* body) = 0;
		};

		class CircleDefinition: public ShapeDefinition{
		public:
			CircleDefinition(float radius, ofVec2f offset=ofVec2f(0,0), float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
			Shape* create(cpSpace *space, cpBody *body) override;
			float radius;
			ofVec2f offset;
		};

		class RectDefinition: public ShapeDefinition{
		public:
			RectDefinition(ofRectangle bounds, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
			Shape* create(cpSpace *space, cpBody *body) override;
			ofRectangle bounds;
		};

		class PolygonDefinition: public ShapeDefinition{
		public:
			PolygonDefinition(std::vector<ofVec2f> points, float radius=0.f, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
			Shape* create(cpSpace *space, cpBody *body) override;
			std::vector<ofVec2f> points;
			float radius;
		};

	public:
		void addCircle(float radius, ofVec2f offset, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addRect(ofRectangle bounds, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addPolygon(ofPolyline poly, float radius=0.f, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addPolygon(std::vector<ofVec2f> points, float radius=0.f, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addConcavePolygon(ofPolyline poly, float precision=1, float radius=0.f, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addConcavePolygon(std::vector<ofVec2f> points, float precision=1, float radius=0.f, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);
		void addLine(ofVec2f a, ofVec2f b, float mass=1, float friction=OFXCHIPMUNK_DEFAULT_FRICTION, float elasticity=OFXCHIPMUNK_DEFAULT_ELASTICITY);

		cpFloat getMass();
		cpFloat getMoment();

		std::vector<shared_ptr<ShapeDefinition>> definitions;

	};

	Composite();
	Composite(cpSpace* space, Definition& def);

	void setup(cpSpace* space, Definition& def);

	void setFriction(float friction, int id=-1);
	void setElasticity(float elasiticity, int id=-1);

	template<typename Type>
	shared_ptr<Type> getShape(int id){
		return std::dynamic_pointer_cast<Type>(getShape(id));
	}

	shared_ptr<Shape> getShape(int id);
	int getNumShapes();

	void setScale(float s);

	ofPath getAsPath();

	void collisionSetGroup(unsigned int group);

    std::vector<std::shared_ptr<DynamicBody>> breakApart();

private:
	void add(Shape* shape);

	std::vector<shared_ptr<Shape>> shapes;

    cpSpace* space;

	float scale;
};

} // namespace ofxChimpunk

#endif // OFXCHIMPUNK_COMPOSITE_H
