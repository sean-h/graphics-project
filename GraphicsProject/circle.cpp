/***********
* circle.cpp
***********/

#include "Angel.h"
#include "shapes.h"

Circle::Circle() { }

Circle::Circle(float radius, int vertexCount, vec2 position, vec3 color)
{
	this->vertexCount = vertexCount;
	this->radius = radius;
	this->position = position;

	//set up vertices in model space
	vertices = new vec2[vertexCount];
	vertices[0] = vec2(0.0f, 0.0f);
	GLfloat angleIncrement = 360.0f / (vertexCount - 2);
	GLfloat angle = 0;
	for (int i = 1; i < vertexCount; ++i) {
		vertices[i] = vec2(cos(angle * DegreesToRadians) * radius, sin(angle * DegreesToRadians) * radius);
		angle += angleIncrement;
	}

	//create vertices used for drawing in world space
	transformedVertices = new vec2[vertexCount];
	colors = new vec3[vertexCount];
	for (int i = 0; i < vertexCount; ++i) {
		transformedVertices[i] = vertices[i] + position;
		colors[i] = color;
	}
}

void Circle::draw(GLuint program) 
{
	Shape::draw(GL_TRIANGLE_FAN, program);
}

float Circle::getRadius()
{
	return this->radius;
}

void Circle::changeRadius(float radius)
{
	if (radius < 0.01f) {
		radius = 0.01f;
	}

	this->radius = radius;

	GLfloat angleIncrement = 360.0f / (vertexCount - 2);
	GLfloat angle = 0;
	for (int i = 1; i < vertexCount; ++i) {
		vertices[i] = vec2(cos(angle * DegreesToRadians) * radius, sin(angle * DegreesToRadians) * radius);
		angle += angleIncrement;
	}
	updateTransformedVertices();
}

void Circle::makeJagged()
{
	GLfloat angleIncrement = 360.0f / (vertexCount - 2);
	GLfloat angle = 0;
	for (int i = 1; i < vertexCount; ++i) {
		float newRadius = radius;
		if (i % 2 == 0) {
			newRadius = radius * 0.75f;
		}

		vertices[i] = vec2(cos(angle * DegreesToRadians) * newRadius, sin(angle * DegreesToRadians) * newRadius);
		angle += angleIncrement;
	}

	updateTransformedVertices();
}