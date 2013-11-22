#include "obstacle.h"
#include "graphics.h"

Obstacle::Obstacle(vec3 pos, vec3 move)
{
	isAlive = true;
	this->model = Sphere(pos, 1.0, YELLOW);
	this->playBoundary = vec2(20.0, 20.0);
	this->moveDirection = move;
}

void Obstacle::update(float deltaTime)
{
	if (model.getPosition().x - model.getRadius() < -playBoundary.x) {
		this->moveDirection.x *= -1;
    }
    else if (model.getPosition().x + model.getRadius() > playBoundary.x) {
		this->moveDirection.x *= -1;
    }
	if (model.getPosition().y - model.getRadius() < 0) {
		this->moveDirection.y *= -1;
    }
    else if (model.getPosition().y + model.getRadius() > 10.0f) {
		this->moveDirection.y *= -1;
    }
	if (model.getPosition().z - model.getRadius() < -playBoundary.y) {
		this->moveDirection.z *= -1;
    }
    else if (model.getPosition().z + model.getRadius() > playBoundary.y) {
		this->moveDirection.z *= -1;
    }

	this->model.move(moveDirection * deltaTime);
}

void Obstacle::draw(mat4 mv, mat4 p, Light light)
{
	if (this->isAlive) {
		this->model.draw(mv, p, light);
	}
}

void Obstacle::onPlayerCollision()
{
	this->isAlive = false;
}

Sphere Obstacle::getModel()
{
	return this->model;
}

bool Obstacle::getIsAlive()
{
	return this->isAlive;
}