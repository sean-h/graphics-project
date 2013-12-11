/***********
* rectangle.cpp
***********/

#include "shapes.h"
#include "Angel.h"

Rect::Rect(vec2 topLeft, float width, float height, vec3 color) { }

Rect::Rect(vec2 topLeft, vec2 bottomRight, vec3 color)
{
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->vertexCount = 4;
	this->position = topLeft;

	vertices = new vec2[vertexCount];
	transformedVertices = new vec2[vertexCount];
	colors = new vec3[vertexCount];
	updateRect();
	
	//set color vertices
	for (int i = 0; i < vertexCount; ++i) {
		colors[i] = color;
	}
}

vec2 Rect::getCenter()
{
	float x = (this->topLeft.x + this->bottomRight.x) / 2;
	float y = (this->topLeft.y + this->bottomRight.y) / 2;
	return vec2(x, y);
}

float Rect::getHeight()
{
	return this->topLeft.y - this->bottomRight.y;
}

float Rect::getWidth()
{
	return this->bottomRight.x - this->topLeft.x;
}

void Rect::draw(GLuint program)
{
	Shape::draw(GL_TRIANGLE_FAN, program);
}

void Rect::updateRect()
{
	vertices[0] = vec2(0.0f, 0.0f);
	vertices[1] = vec2(0.0f, bottomRight.y - topLeft.y);
	vertices[2] = bottomRight - topLeft;
	vertices[3] = vec2(bottomRight.x - topLeft.x, 0.0f);

	for (int i = 0; i < vertexCount; ++i) {
		transformedVertices[i] = vertices[i] + position;
	}
}

void Rect::setWidth(float width)
{
	this->bottomRight = vec2(this->topLeft.x + width, this->bottomRight.y);
	updateRect();
}

void Rect::setHeight(float height)
{
	this->bottomRight = vec2(this->bottomRight.x, this->topLeft.y - height);
	updateRect();
}