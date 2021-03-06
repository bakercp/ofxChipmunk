#include "ofxChipmunkShape.h"
#include "ofxChipmunkUtils.h"

namespace ofxChipmunk {

Shape::Shape():shape(nullptr){

}

Shape::~Shape(){
    if(shape){
        cpSpaceRemoveShape(cpShapeGetSpace(shape), shape);
        cpShapeFree(shape);
		shape = nullptr;
    }
}

void Shape::setup(cpSpace *space, cpShape *s){
    shape = cpSpaceAddShape(space, s);
    setFriction(OFXCHIPMUNK_DEFAULT_FRICTION);
    setElasticity(OFXCHIPMUNK_DEFAULT_ELASTICITY);
}

void Shape::setElasticity(float value){
    cpShapeSetElasticity(shape, value);
}

void Shape::setFriction(float friction){
    cpShapeSetFriction(shape, friction);
}

void Shape::collisionSetGroup(unsigned int group){
    cpShapeFilter filter = cpShapeGetFilter(shape);
    filter.group = group;
    cpShapeSetFilter(shape, filter);
}

unsigned int Shape::collisionGetGroup(){
    cpShapeFilter filter = cpShapeGetFilter(shape);
    return filter.group;
}


/*
void Shape::collisionSetCategory(unsigned int category){
    cpShapeFilter filter = cpShapeGetFilter(shape);
    //if(filter.categories == CP_ALL_CATEGORIES)
    filter.categories = category;
    //else
        //filter.categories |= category;

    cpShapeSetFilter(shape, filter);
}

void Shape::collisionDisableWithCategory(unsigned int category){
    cpShapeFilter filter = cpShapeGetFilter(shape);
    filter.mask = ~category;
    cpShapeSetFilter(shape, filter);
}

void Shape::collisionEnableWithCategory(unsigned int category){
    cpShapeFilter filter = cpShapeGetFilter(shape);
    filter.mask = category;
    cpShapeSetFilter(shape, filter);
}

void Shape::setCollisionType(int typeId){
    //cpShapeFilterNew()
    //cpShapeSetFilter(shape, groupId);
    cpShapeSetCollisionType(shape, typeId);
}

void Shape::setCollisionFilter(unsigned int group, unsigned int categories, unsigned int mask){
    cpShapeSetFilter(shape, cpShapeFilterNew(group, categories, mask));
}
*/

//
ShapeCircle::ShapeCircle(){

}

ShapeCircle::ShapeCircle(cpSpace *space, cpBody *body, float radius, glm::vec2 offset){
    setup(space, body, radius, offset);
}

void ShapeCircle::setup(cpSpace *space, cpBody* body, float radius, glm::vec2 offset){
    radiusInitial = radius;
    offsetInitial = offset;
    Shape::setup(space, cpCircleShapeNew(body, radius, toChipmunk(offset)));
}

void ShapeCircle::setup(ShapeCircle *src){
    radiusInitial = src->radiusInitial;
    offsetInitial = src->offsetInitial;
    shape = src->shape;
    src->shape = nullptr;
}

void ShapeCircle::setRadius(float r){
    cpCircleShapeSetRadius(shape, r);
}

float ShapeCircle::getRadius(){
    return cpCircleShapeGetRadius(shape);
}


void ShapeCircle::setOffset(glm::vec2 off){
    cpCircleShapeSetOffset(shape, toChipmunk(off));
}

glm::vec2 ShapeCircle::getOffset(){
    return toOf(cpCircleShapeGetOffset(shape));
}

void ShapeCircle::scale(float s){
    setRadius(radiusInitial*s);
    setOffset(offsetInitial*s);
}

ofPath ShapeCircle::getAsPath(){
    ofPath ret;
    ret.circle(toOf(cpCircleShapeGetOffset(shape)), getRadius());
    return ret;
}

Shape::Type ShapeCircle::getType(){
    return Shape::Type::Circle;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShapeRect::ShapeRect(){

}

ShapeRect::ShapeRect(cpSpace *space, cpBody *body, ofRectangle bounds, float radius){
	setup(space, body, bounds, radius);
}

void ShapeRect::scale(float s){
	//cpPolyShapeSetRadius(shape, s);
	scale(s, s);
}

void ShapeRect::scale(glm::vec2 s){
	scale(s.x, s.y);
}

void ShapeRect::scale(float sx, float sy){
	curScaleX = sx;
	curScaleY = sy;

	std::vector<cpVect> pts;
	for(int i=0; i<numPoints; i++){
		pts.push_back({points[i].x*curScaleX, points[i].y*curScaleY});
	}

	cpPolyShapeSetVertsRaw(shape, numPoints, pts.data());
	cpShapeCacheBB(shape);
}

glm::vec2 ShapeRect::getScale(){
	return glm::vec2(curScaleX, curScaleY);
}

void ShapeRect::setup(cpSpace *space, cpBody *body, ofRectangle bounds, float radius){
    Shape::setup(space, cpBoxShapeNew(body, bounds.width, bounds.height, radius));

	curScaleX = curScaleY = 1;

	numPoints = 4;
	points = new cpVect[numPoints];
	for(int i=0; i<numPoints; i++){
		points[i] = cpPolyShapeGetVert(shape, i);
	}
}

Shape::Type ShapeRect::getType(){
    return Shape::Type::Rectangle;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShapeLine::ShapeLine(){

}

ShapeLine::ShapeLine(cpSpace *space, cpBody* body,glm::vec2 a, glm::vec2 b, float radius){
    setup(space, body, a, b, radius);
}

void ShapeLine::setup(cpSpace *space, cpBody* body,glm::vec2 a, glm::vec2 b, float radius){
    aInitial = a;
    bInitial = b;
    radiusInitial = radius;
    Shape::setup(space, cpSegmentShapeNew(body, toChipmunk(a), toChipmunk(b), radius));
}

void ShapeLine::setup(ShapeLine *src){
    aInitial = src->aInitial;
    bInitial = src->bInitial;
    shape = src->shape;
    src->shape = nullptr;
}

glm::vec2 ShapeLine::getA(){
    return toOf(cpSegmentShapeGetA(shape));
}

glm::vec2 ShapeLine::getB(){
    return toOf(cpSegmentShapeGetB(shape));
}

float ShapeLine::getRadius(){
    return cpSegmentShapeGetRadius(shape);
}

void ShapeLine::scale(float s){
    cpSegmentShapeSetEndpoints(shape, toChipmunk(aInitial*s), toChipmunk(bInitial*s));
}

ofPath ShapeLine::getAsPath(){
    ofPath ret;
    ret.moveTo(getA());
    ret.lineTo(getB());
    return ret;
}

Shape::Type ShapeLine::getType(){
    return Shape::Type::Line;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShapePolygon::ShapePolygon(){numPoints=0;curScale=1;}

ShapePolygon::~ShapePolygon(){
    free(points);
}

ShapePolygon::ShapePolygon(cpSpace *space, cpBody *body, ofPolyline poly, float radius){
    numPoints=0;
	setup(space, body, poly, radius);
}

ShapePolygon::ShapePolygon(cpSpace *space, cpBody *body, std::vector<glm::vec2> &points, float radius){
    numPoints = 0;
	setup(space, body, points, radius);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, ofPolyline poly, float radius){
	std::vector<glm::vec2> vecs;
    for(auto& p: poly){
		vecs.push_back(glm::vec2(p.x, p.y));
    }
	setup(space, body, vecs, radius);
	curScale = 1;
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, std::vector<glm::vec2> &points, float radius){
	setup(space, body, points.size(), toChipmunk(points).data(), radius);
}

void ShapePolygon::setup(ShapePolygon *src){
    numPoints = src->numPoints;
    points = new cpVect[numPoints];
    memcpy(points, src->points, numPoints*sizeof(cpVect));
    shape = src->shape;
    src->shape = nullptr;
	scale(src->curScale);
}

void ShapePolygon::setRadius(float radius){
	cpPolyShapeSetRadius(shape, radius);
}

void ShapePolygon::scale(float s){

    /*
    int nPts = cpPolyShapeGetCount(shape);

    std::vector<cpVect> pts(nPts);
    for(int i=0; i<nPts; i++){
        pts.push_back(cpvmult(cpPolyShapeGetVert(shape, i), s));
    }
    */

	curScale = s;

    std::vector<cpVect> pts;
    for(int i=0; i<numPoints; i++){
        pts.push_back(cpvmult(points[i], s));
    }

    //cpTransformIdentity;
    //cpPolyShapeSetVerts(shape, numPoints, pts.data(), cpTransformIdentity);
    cpPolyShapeSetVertsRaw(shape, numPoints, pts.data());
    cpShapeCacheBB(shape);
}

ofPath ShapePolygon::getAsPath(){
    ofPath ret;
	for(int i=0; i<cpPolyShapeGetCount(shape); i++){
		ret.lineTo(toOf(cpPolyShapeGetVert(shape, i)));
    }
    ret.close();
    return ret;
}

Shape::Type ShapePolygon::getType(){
    return Shape::Type::Polygon;
}

std::vector<glm::vec2> ShapePolygon::getPoints(){
	std::vector<glm::vec2> ret;
    for(unsigned int i=0; i<numPoints; i++){
		ret.push_back(toOf(points[i])*curScale);
    }
	return ret;
}

const cpVect findCentroid(cpVect* pts, size_t nPts){
	cpVect off = pts[0];
	float twicearea = 0;
	float x = 0;
	float y = 0;
	cpVect p1, p2;
	float f;
	for (int i = 0, j = nPts - 1; i < nPts; j = i++) {
		p1 = pts[i];
		p2 = pts[j];
		f = (p1.x - off.x) * (p2.y - off.y) - (p2.x - off.x) * (p1.y - off.y);
		twicearea += f;
		x += (p1.x + p2.x - 2 * off.x) * f;
		y += (p1.y + p2.y - 2 * off.y) * f;
	}

	f = twicearea * 3;

	return {x / f + off.x, y / f + off.y};
}

glm::vec2 ShapePolygon::getCenter(){
	return toOf(findCentroid(points, numPoints))*curScale;
}

void ShapePolygon::setOffset(glm::vec2 o){
	std::vector<cpVect> pts(numPoints);


	cpVect off = toChipmunk(o);
	for(int i=0;i<numPoints;i++){
		pts[i] = cpvadd(cpvmult(points[i], curScale), off);
		points[i] = cpvadd(points[i], off);
	}
	cpPolyShapeSetVertsRaw(shape, numPoints, pts.data());
	cpShapeCacheBB(shape);
}

void ShapePolygon::setup(cpSpace *space, cpBody *body, int nPoints, cpVect *verts, float radius){
    if(numPoints>0){
        free(points);
    }

    numPoints = nPoints;
    points = new cpVect[numPoints];
    memcpy(points, verts, numPoints*sizeof(cpVect));

	Shape::setup(space, cpPolyShapeNew(body, nPoints, verts, cpTransformIdentity, radius));

    /*
    numPoints = cpPolyShapeGetCount(shape);
    points = new cpVect[numPoints];
    for(int i=0;i<numPoints;i++){
        points[i] = cpPolyShapeGetVert(shape, i);
    }
    */
}



//

} // namespace ofxChimpunk
