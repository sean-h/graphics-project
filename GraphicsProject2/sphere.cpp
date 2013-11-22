/***********
* sphere.cpp
***********/
#include "shapes.h"
#include "Angel.h"
#include <iostream>

Sphere::Sphere() { }

Sphere::Sphere(vec3 pos, GLfloat r, color4 color)
{
	position = pos;
	radius = r;
	scale = vec3(r, r, r);
	rotation = vec3(0.0, 0.0, 0.0);
	index = 0;
	numVertices = 3 * 4096;
	points = new point4[numVertices];
	normals = new vec3[numVertices];
	diffuse = color;
	ambient = color4(0.0, 0.0, 0.0, 1.0);
	specular = color4(0.5, 0.5, 0.5, 1.0);
	shininess = 10.0;
	
	for (int i = 0; i < numVertices; i++) {
		points[i] = point4(0.0, 0.0, 0.0, 1.0);
	}
	
	tetrahedron(5);
	setUpShader();
}

void Sphere::triangle(const point4& a, const point4& b, const point4& c)
{
	vec3 normal = normalize(cross(b - a, c - b));

	normals[index] = normal;
	points[index] = a;
	index++;

	normals[index] = normal;
	points[index] = b;
	index++;

	normals[index] = normal;
	points[index] = c;
	index++;
}

void Sphere::tetrahedron(int count)
{
	point4 v[4];
	v[0] = vec4(0.0, 0.0, 1.0, 1.0);
	v[1] = vec4(0.0, 0.942809, -0.333333, 1.0);
	v[2] = vec4(-0.816497, -0.471405, -0.333333, 1.0);
	v[3] = vec4(0.816497, -0.471405, -0.333333, 1.0);

	divideTriangle(v[0], v[1], v[2], count);
	divideTriangle(v[3], v[2], v[1], count);
	divideTriangle(v[0], v[3], v[1], count);
	divideTriangle(v[0], v[2], v[3], count);
}

void Sphere::divideTriangle(const point4& a, const point4& b, const point4& c, int count)
{
	if (count > 0) {
		point4 v1 = unit(a + b);
		point4 v2 = unit(a + c);
		point4 v3 = unit(b + c);
		divideTriangle(a, v1, v2, count - 1);
		divideTriangle(c, v2, v3, count - 1);
		divideTriangle(b, v3, v1, count - 1);
		divideTriangle(v1, v3, v2, count - 1);
	} else {
		triangle(a, b, c);
	}
}

point4 Sphere::unit(const point4& p)
{
	float len = p.x * p.x + p.y * p.y + p.z * p.z;

	point4 t;
	if (len > DivideByZeroTolerance) {
		t = p / sqrt(len);
		t.w = 1.0;
	}

	return t;
}

float Sphere::getRadius()
{
	return radius;
}

void Sphere::setRadius(float r)
{
	this->radius = r;
	setScale(r, r, r);
}

void Sphere::setScale(float x, float y, float z)
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;
}