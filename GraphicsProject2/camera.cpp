/***********
* camera.cpp
***********/
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
	this->theta = 3.14 / 2.0;
	this->orbitSpeed = 1.0;
	this->zoomSpeed = 10.0;
	this->radius = 40;
	rotate(0);
}

void Camera::update(Input input, float deltaTime)
{
	if (input.isKeyDown('t'))
	{
		rotate(-orbitSpeed * deltaTime);
	}
	if (input.isKeyDown('y'))
	{
		rotate(orbitSpeed * deltaTime);
	}

	if (input.isKeyDown('g'))
	{
		zoom(-zoomSpeed * deltaTime);
	}
	if (input.isKeyDown('h'))
	{
		zoom(zoomSpeed * deltaTime);
	}
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

void Camera::rotate(float angle)
{
	this->theta += angle;

	position = vec3(radius*sin(theta), radius, radius*cos(theta));
}

void Camera::zoom(float amount)
{
	this->radius += amount;
	rotate(0);
}