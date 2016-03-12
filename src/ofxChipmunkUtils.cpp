#include "ofxChipmunkUtils.h"

#include <chipmunk_structs.h>

namespace ofxChipmunk {

cpVect toChipmunk(ofVec2f v){
	return {v.x, v.y};
}

ofVec2f toOf(cpVect v){
	return ofVec2f(v.x, v.y);
}

//

cpBB toChipmunk(ofRectangle rect){
	return {rect.getLeft(), rect.getBottom(), rect.getRight(), rect.getTop()};
}

ofRectangle toOf(cpBB rect){
	return ofRectangle(rect.l, rect.t, rect.r-rect.l, rect.b - rect.t);
}

///////// DRAWING

static inline cpSpaceDebugColor RGBAColor(float r, float g, float b, float a){
	cpSpaceDebugColor color = {r, g, b, a};
	return color;
}

static inline cpSpaceDebugColor LAColor(float l, float a){
	cpSpaceDebugColor color = {l, l, l, a};
	return color;
}

static cpSpaceDebugColor ColorForShape(cpShape *shape, cpDataPointer data) {
	if(cpShapeGetSensor(shape)){
		return LAColor(1.0f, 0.1f);
	} else {
		cpBody *body = cpShapeGetBody(shape);

		if(cpBodyIsSleeping(body)){
			return LAColor(0.2f, 1.0f);
		} else if(body->sleeping.idleTime > shape->space->sleepTimeThreshold) {
			return LAColor(0.66f, 1.0f);
		} else {
			uint32_t val = (uint32_t)shape->hashid;

			// scramble the bits up using Robert Jenkins' 32 bit integer hash function
			val = (val+0x7ed55d16) + (val<<12);
			val = (val^0xc761c23c) ^ (val>>19);
			val = (val+0x165667b1) + (val<<5);
			val = (val+0xd3a2646c) ^ (val<<9);
			val = (val+0xfd7046c5) + (val<<3);
			val = (val^0xb55a4f09) ^ (val>>16);

			GLfloat r = (GLfloat)((val>>0) & 0xFF);
			GLfloat g = (GLfloat)((val>>8) & 0xFF);
			GLfloat b = (GLfloat)((val>>16) & 0xFF);

			GLfloat max = (GLfloat)cpfmax(cpfmax(r, g), b);
			GLfloat min = (GLfloat)cpfmin(cpfmin(r, g), b);
			GLfloat intensity = (cpBodyGetType(body) == CP_BODY_TYPE_STATIC ? 0.15f : 0.75f);

			// Saturate and scale the color
			if(min == max){
				return RGBAColor(intensity, 0.0f, 0.0f, 1.0f);
			} else {
				GLfloat coef = (GLfloat)intensity/(max - min);
				return RGBAColor(
					(r - min)*coef,
					(g - min)*coef,
					(b - min)*coef,
					1.0f
				);
			}
		}
	}
}

static ofColor toOf(cpSpaceDebugColor& color){
	return ofFloatColor(color.r, color.g, color.b, color.a);
}

static cpSpaceDebugDrawOptions drawOptions = {
	drawCircle,
	drawSegment,
	drawFatSegment,
	drawPolygon,
	drawDot,

    (cpSpaceDebugDrawFlags)(CP_SPACE_DEBUG_DRAW_SHAPES | CP_SPACE_DEBUG_DRAW_CONSTRAINTS | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS),

	{200.0f/255.0f, 210.0f/255.0f, 230.0f/255.0f, 1.0f},
	ColorForShape,
	{0.0f, 0.75f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 1.0f},
	NULL,
};

void drawSpace(cpSpace *space){
	ofPushStyle();
	cpSpaceDebugDraw(space, &drawOptions);
	ofPopStyle();
}

void drawCircle(cpVect p, cpFloat a, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data){
    ofSetColor(toOf(fill));
	ofFill();
	ofDrawCircle(toOf(p), r);

    ofSetLineWidth(1);
	ofSetColor(toOf(outline));
	ofNoFill();
	ofDrawCircle(toOf(p), r);
}

void drawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data){
    ofSetLineWidth(1);
    ofNoFill();
    ofSetColor(toOf(color));
    ofDrawLine(toOf(a), toOf(b));
}

void drawFatSegment(cpVect a, cpVect b, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data){
    ofSetLineWidth(r);
    ofSetColor(toOf(fill));
    ofDrawLine(toOf(a), toOf(b));
}

static ofMesh polyMesh;
static ofTessellator tesselator;

void drawPolygon(int count, const cpVect *verts, cpFloat r, cpSpaceDebugColor outline, cpSpaceDebugColor fill, cpDataPointer data){
	ofPolyline poly;

    for(int i=0; i<count;i++){
        poly.addVertex(toOf(verts[i]));
		ofDrawCircle(toOf(verts[i]), 2);
    }
    poly.close();

	ofSetColor(toOf(fill));
	ofFill();

	ofBeginShape();
	for(auto p: poly){
		ofVertex(p);
	}
	ofEndShape();

	//tesselator.tessellateToMesh(poly, ofPolyWindingMode::OF_POLY_WINDING_POSITIVE, polyMesh, true);
	//polyMesh.drawFaces();

	ofSetColor(toOf(outline));
	ofNoFill();
	poly.draw();
}

void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data){
    ofFill();
    ofSetColor(toOf(color));
	ofDrawCircle(toOf(pos), size);
}

std::vector<cpVect> toChipmunk(std::vector<ofVec2f>& points){
	std::vector<cpVect> ret;
	for(auto& p: points){
		ret.push_back(toChipmunk(p));
	}
	return ret;
}


} // namespace ofxChipmunk
