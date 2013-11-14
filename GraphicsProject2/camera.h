#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Angel.h"

class Camera
{
private:
	GLfloat fovy;
	GLfloat zNear;
	GLfloat zFar;
	GLfloat aspect;
	vec4 position;
	vec4 up;
	vec4 at;
public:
	Camera(vec3 pos);
	mat4 getLookAt();
	mat4 getPerspective();
	void setAspect(GLfloat);
};

#endif