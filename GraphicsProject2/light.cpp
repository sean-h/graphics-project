#include "light.h"

Light::Light(point4 pos, color4 amb, color4 diff, color4 spec)
{
	this->position = pos;
	this->ambient = amb;
	this->diffuse = diff;
	this->specular = spec;
}