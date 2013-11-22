/***********
* light.h
***********/
#pragma once

#include "graphics.h"

class Light
{
private:
	
public:
	Light(point4 pos, color4 amb, color4 diff, color4 spec);
	point4 position;
	color4 ambient;
	color4 diffuse;
	color4 specular;
	bool isEnabled;
};