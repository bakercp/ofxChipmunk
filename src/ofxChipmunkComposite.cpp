#include "ofxChipmunkComposite.h"

namespace ofxChipmunk {

Composite::Composite(){

}

void Composite::setup(cpSpace *s){
    //Body::setup();
    space = s;
}

void Composite::addCircle(ofVec2f offset, float radius, float mass){
    TempCircle tmp;
    tmp.mass = mass;
    tmp.moment = cpMomentForCircle(mass, 0, radius, toChipmunk(offset));
    tmp.offset = offset;
    tmp.radius = radius;
    tmpCircles.push_back(tmp);
}

void Composite::build(){
    cpFloat mass = 0;
    cpFloat moment = 0;

    for(auto& t: tmpCircles){
        mass += t.mass;
        moment += t.moment;
    }
    for(auto& t: tmpRects){
        mass += t.mass;
        moment += t.moment;
    }
    for(auto& t: tmpPolys){
        mass += t.mass;
        moment += t.moment;
    }

    Body::setup(space, mass, moment);

    for(auto& c: tmpCircles){
        ShapeCircle* shape = new ShapeCircle();
        shape->setup(space, body, c.radius);
        add(shape);
    }
}

void Composite::add(Shape *shape){
    shapes.push_back(std::shared_ptr<Shape>(shape));
}

} // namespace ofxChimpunk
