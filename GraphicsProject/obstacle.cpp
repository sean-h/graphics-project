/***********
* obstacle.cpp
***********/

#include "obstacle.h"
#include <iostream>

Obstacle::Obstacle() { }

Obstacle::Obstacle(vec2 position)
{
	this->isAlive = true;
	this->model = Circle(0.02f, 25, position, vec3(1.0f, 0.8f, 0.0f));

	//generate random numbers between -100 and 100
	int randX = (rand() % 200) - 100;
	int randY = (rand() % 200) - 100;
	this->moveDirection = vec2(randX, randY);
	this->moveDirection = normalize(this->moveDirection);
	this->moveSpeed = 0.1f;
}

void Obstacle::update(float deltaTime)
{
	vec2 move = moveDirection * moveSpeed * deltaTime;
	model.move(move);

	if (this->model.getPosition().x <= -1.0f || this->model.getPosition().x >= 1.0f) {
		this->moveDirection.x *= -1.0f;
	}

	if (this->model.getPosition().y <= -1.0f || this->model.getPosition().y >= 1.0f) {
		this->moveDirection.y *= -1.0f;
	}
}

void Obstacle::draw(GLuint program)
{
	model.draw(program);
}

vec2 Obstacle::getPosition()
{
	return this->model.getPosition();
}

Circle Obstacle::getModel()
{
	return this->model;
}

void Obstacle::onPlayerCollision()
{
	this->isAlive = false;
}

bool Obstacle::getIsAlive()
{
	return this->isAlive;
}