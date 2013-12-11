/***********
* shape.cpp
***********/

#include "Angel.h"
#include "shapes.h"
#include <iostream>

Shape::Shape() 
{
	vertexCount = 3;

	vertices = new vec2[3];
	vertices[0] = vec2(-0.5f, 0.0f);
	vertices[1] = vec2(0.5f, 0.0f);
	vertices[2] = vec2(0.0f, 0.5f);

	transformedVertices = new vec2[vertexCount];
	for (int i = 0; i < vertexCount; ++i) {
		transformedVertices[i] = vertices[i];
	}

	colors = new vec3[3];
	colors[0] = vec3(0.0f, 1.0f, 0.0f);
	colors[1] = vec3(1.0f, 0.0f, 0.0f);
	colors[2] = vec3(0.0f, 0.0f, 1.0f);

	glGenBuffers(1, &buffer);
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
}

void Shape::draw(GLuint program) 
{
	draw(GL_TRIANGLES, program);
}

void Shape::draw(GLenum mode, GLuint program)
{
	int vertexSize = sizeof(vec2) * vertexCount;
	int colorSize = sizeof(vec3) * vertexCount;
	int bufferSize = vertexSize + colorSize;
	glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize, transformedVertices);
	glBufferSubData(GL_ARRAY_BUFFER, vertexSize, colorSize, colors);

	auto loc2 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSize));

	glDrawArrays(mode, 0, vertexCount);
}

void Shape::move(float x, float y) 
{
	move(vec2(x, y));
}

void Shape::move(vec2 moveAmount)
{
	position += moveAmount;
	for (int i = 0; i < vertexCount; ++i) {
		transformedVertices[i] += moveAmount;
	}
}

void Shape::rotate(float angle)
{
	for (int i = 0; i < vertexCount; ++i) {
		float x = (cos(angle) * (transformedVertices[i].x - position.x)) - (sin(angle) * (transformedVertices[i].y - position.y));
		float y = (sin(angle) * (transformedVertices[i].x - position.x)) + (cos(angle) * (transformedVertices[i].y - position.y));
		transformedVertices[i].x = x + position.x;
		transformedVertices[i].y = y + position.y;
	}
}

void Shape::setPosition(float x, float y)
{
	setPosition(vec2(x, y));
}

void Shape::setPosition(vec2 position) 
{
	this->position = position;
	updateTransformedVertices();
}

vec2 Shape::getPosition()
{
	return this->position;
}

void Shape::setColor(vec3 color)
{
	for (int i = 0; i < vertexCount; ++i) {
		this->colors[i] = color;
	}
}

void Shape::updateTransformedVertices()
{
	for (int i = 0; i < vertexCount; ++i) {
		transformedVertices[i] = vertices[i] + position;
	}
}

void Shape::setVertexColor(int vertex, vec3 color)
{
	this->colors[vertex] = color;
}