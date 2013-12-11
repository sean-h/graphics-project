/***********
* collision.cpp
***********/

#include "collision.h"
#include "shapes.h"

bool circleCollision(Circle c1, Circle c2)
{
	vec2 pos1 = c1.getPosition();
	vec2 pos2 = c2.getPosition();
	float r1 = c1.getRadius();
	float r2 = c2.getRadius();

	float distance = getDistance(pos1, pos2);
	if (distance - r1 - r2 <= 0) {
		return true;
	}

	return false;
}

float getDistance(vec2 pos1, vec2 pos2)
{
	float dX = abs(pos1.x - pos2.x);
	float dY = abs(pos1.y - pos2.y);
	return sqrt((dX * dX) + (dY * dY));
}