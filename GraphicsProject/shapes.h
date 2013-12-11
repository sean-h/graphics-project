/***********
* shapes.h
***********/

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include "Angel.h"
#include <vector>

class Shape {
protected:
	vec2 position;
	int vertexCount;
	vec2 *vertices;
	vec2 *transformedVertices;
	vec3 *colors;
	GLuint buffer;
	void draw(GLenum, GLuint);
public:
	Shape();
	void draw(GLuint);
	void move(float, float);
	void move(vec2);
	void rotate(float);
	void setPosition(float, float);
	void setPosition(vec2);
	vec2 getPosition();
	void setColor(vec3);
	void setVertexColor(int, vec3);
	void updateTransformedVertices();
};

class Circle : public Shape {
private:
	float radius;
public:
	Circle();
	Circle(float, int, vec2, vec3);
	void draw(GLuint);
	float getRadius();
	void changeRadius(float);
	void makeJagged();
};

class Rect : public Shape {
private:
	vec2 topLeft;
	vec2 bottomRight;
	void updateRect();
public:
	Rect(vec2, float, float, vec3);
	Rect(vec2, vec2, vec3);
	vec2 getCenter();
	vec2 getTopLeft();
	vec2 getBottomRight();
	float getHeight();
	float getWidth();
	void draw(GLuint);
	void setWidth(float);
	void setHeight(float);
};

#endif