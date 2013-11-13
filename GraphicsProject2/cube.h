#ifndef __CUBE_H__
#define __CUBE_H__

#include "Angel.h"
#include "graphics.h"

class Cube
{
private:
	int numVertices;
	point4 points[36];
	color4 colors[36];
	point4 vertices[8];
	color4 vertex_colors[8];
	GLuint buffer;
	vec3 position;
	GLuint program;
	GLuint positionMat;
	GLuint modelViewMat;
	GLuint projectionMat;
	void colorcube();
	int quadIndex;
	void quad(int a, int b, int c, int d);
public:
	Cube(vec3 pos);
	void setUpShader();
	int getNumVertices();
	void draw(mat4 mv, mat4 p);
};

#endif