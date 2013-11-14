#pragma once
#include "vec.h"
#include "shapes.h"

bool collides(Sphere a, Sphere b)
{
	float distance = length(a.getPosition() - b.getPosition());
	float r = a.getRadius() + b.getRadius();
	return (distance <= r);
}