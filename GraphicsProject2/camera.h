#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Angel.h"
#include "input.h"

class Camera
{
private:
	GLfloat fovy;
	GLfloat zNear;
	GLfloat zFar;
	GLfloat aspect;
	float radius;
	vec4 position;
	vec4 up;
	vec4 at;
	float theta;
	float orbitSpeed;
	float zoomSpeed;
public:
	Camera(vec3 pos);
	void update(Input input, float deltaTime);
	mat4 getLookAt();
	mat4 getPerspective();
	void setAspect(GLfloat);
	void rotate(float angle);
	void zoom(float amount);
};

#endif