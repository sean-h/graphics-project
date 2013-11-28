/***********
* shapes.h
***********/
#pragma once

#include "Angel.h"
#include "graphics.h"
#include "light.h"

class Shape
{
protected:
    int numVertices;
    point4 *points;
    vec3 *normals;
    point4 *vertices;
    color4 *vertex_colors;
    GLuint buffer;
    vec3 position;
    vec3 scale;
    vec3 rotation;
    GLuint program;
    GLuint positionMat;
    GLuint modelViewMat;
    GLuint projectionMat;
    GLuint rotationMat;
    GLuint scaleMat;
    GLuint normalMat;
    color4 diffuse;
    color4 ambient;
    color4 specular;
    float shininess;
public:
    Shape();
    int getNumVertices();
    void setUpShader();
    void draw();
    void draw(mat4 mv, mat4 p, Light light);
    void move(vec3 amount);
    vec3 getPosition();
    vec3 getScale();
    void setPosition(vec3 pos);
    void setScale(float x, float y, float z);
    void rotate(float x, float y, float z);
    void setColor(color4 color);
    void setScaleX(float x);
    void setScaleY(float y);
    void setScaleZ(float z);
};

class Cube : public Shape
{
private:
    void colorcube();
    int quadIndex;
    void quad(int a, int b, int c, int d);
public:
    Cube();
    Cube(vec3 pos, vec3 s);
};

class Sphere : public Shape
{
private:
    GLfloat radius;
    void triangle(const point4& a, const point4& b, const point4& c);
    void tetrahedron(int count);
    void divideTriangle(const point4& a, const point4& b, const point4& c, int count);
    int index;
    point4 unit(const point4& p);
public:
    Sphere();
    Sphere(vec3 pos, GLfloat r, color4 color);
    float getRadius();
    void setRadius(float r);
};