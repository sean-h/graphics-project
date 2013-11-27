/***********
* light.h
***********/
#pragma once

#include "graphics.h"
#include "input.h"

class Light
{
private:
	void move(vec3 amount);
	float moveSpeed;
public:
	Light(point4 pos, color4 amb, color4 diff, color4 spec);
	point4 position;
	color4 ambient;
	color4 diffuse;
	color4 specular;
	bool isEnabled;
	void update(Input input, float deltaTime);
};