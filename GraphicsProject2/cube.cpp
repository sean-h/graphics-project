#include "shapes.h"

Cube::Cube() { }

Cube::Cube(vec3 pos, vec3 s)
{
	numVertices = 36;
	quadIndex = 0;
	position = pos;
	scale = s;
	points = new point4[numVertices];
	normals = new vec3[numVertices];

	diffuse = color4(0.2, 0.2, 0.6, 1.0);
	ambient = color4(1.0, 1.0, 1.0, 1.0);
	specular = color4(1.0, 1.0, 1.0, 1.0);
	shininess = 100.0;

	vertices = new point4[8];
	vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );
    vertices[4] = point4( -0.5, -0.5, -0.5, 1.0 );
    vertices[5] = point4( -0.5,  0.5, -0.5, 1.0 );
    vertices[6] = point4(  0.5,  0.5, -0.5, 1.0 );
    vertices[7] = point4(  0.5, -0.5, -0.5, 1.0 );

	vertex_colors = new point4[8];
	vertex_colors[0] = color4( 0.0, 0.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 1.0, 0.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[3] = color4( 0.0, 1.0, 0.0 , 1.0 );
    vertex_colors[4] = color4( 0.0, 0.0, 1.0, 1.0 );
    vertex_colors[5] = color4( 1.0, 0.0, 1.0, 1.0 );
    vertex_colors[6] = color4( 1.0, 1.0, 1.0, 1.0 );
    vertex_colors[7] = color4( 0.0, 1.0, 1.0, 1.0 );

	colorcube();
	setUpShader();
}

void Cube::colorcube()
{
	quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

void Cube::quad(int a, int b, int c, int d)
{
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];

	vec3 normal = normalize(cross(u, v));

	normals[quadIndex] = normal; points[quadIndex] = vertices[a]; quadIndex++;
    normals[quadIndex] = normal; points[quadIndex] = vertices[b]; quadIndex++;
    normals[quadIndex] = normal; points[quadIndex] = vertices[c]; quadIndex++;
    normals[quadIndex] = normal; points[quadIndex] = vertices[a]; quadIndex++;
    normals[quadIndex] = normal; points[quadIndex] = vertices[c]; quadIndex++;
    normals[quadIndex] = normal; points[quadIndex] = vertices[d]; quadIndex++;
}