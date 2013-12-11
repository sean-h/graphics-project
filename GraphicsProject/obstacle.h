/***********
* obstacle.h
***********/

#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include "Angel.h"
#include "shapes.h"

class Obstacle
{
private:
	bool isAlive;
	float moveSpeed;
	vec2 moveDirection;
	Circle model;
public:
	Obstacle();
	Obstacle(vec2);
	void update(float);
	vec2 getPosition();
	void draw(GLuint);
	Circle getModel();
	void onPlayerCollision();
	bool getIsAlive();
};

#endif