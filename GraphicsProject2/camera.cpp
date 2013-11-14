#include "camera.h"
#include "graphics.h"

Camera::Camera(vec3 pos)
{
	this->position = vec4(pos.x, pos.y, pos.z, 1.0);
	this->fovy = 45.0;
	this->up = vec4(0.0, 1.0, 0.0, 0.0);
	this->at = point4(0.0, 0.0, 0.0, 1.0);
	this->zNear = 0.1;
	this->zFar = 300;
}

mat4 Camera::getLookAt()
{
	return LookAt(position, at, up);
}

mat4 Camera::getPerspective()
{
	return Perspective(fovy, aspect, zNear, zFar);
}

void Camera::setAspect(GLfloat aspect)
{
	this->aspect = aspect;
}