/***********
* player.cpp
***********/

#include "player.h"
#include "Angel.h"
#include "shapes.h"

Player::Player(int playerNumber)
{
	this->playerNumber = playerNumber;
	this->moveSpeed = 0.4f;
	this->score = 0;
	this->movementBudget= 10.0f;
	this->distanceMoved = 0.0f;
	this->bounceTimer = 0.0f;
	this->collisionBounceTime = 0.5f;
	this->defaultRadius = 0.06f;
	this->scoreCounters.clear();

	float side;
	float columnDisplace;
	if (playerNumber == 1) {
		side = -0.95f;
		columnDisplace = 0.05f;
	}
	else {
		side = 0.95f;
		columnDisplace = -0.05f;
	}

	for (int c = 0; c < 5; ++c) {
		for (int i = 0; i < 20; ++i) {
			Rect *r = new Rect(vec2(side + (c * columnDisplace), 0.9f - (float)i / 50.0f),
				vec2(side + 0.01f + (c * columnDisplace), 0.89f - (float)i / 50.0f),
				vec3(1.0f, 0.0f, 0.0f));
			scoreCounters.push_back(r);
		}
	}

	vec3 modelColor;
	vec2 position;
	vec3 radialColor;
	if (playerNumber == 1) {
		modelColor = vec3(1.0f, 0.0f, 0.0f);
		position = vec2(-0.5f, 0.0f);
		radialColor = vec3(0.0f, 1.0f, 0.0f);
	}
	else if (playerNumber == 2) {
		modelColor = vec3(0.0f, 0.0f, 1.0f);
		position = vec2(0.5f, 0.0f);
		radialColor = vec3(1.0f, 0.0f, 0.0f);
	}

	this->playerModel = Circle(0.06f, 31, position, modelColor);
	this->playerModel.setVertexColor(0, radialColor);
	this->playerModel.setVertexColor(1, radialColor);
}

void Player::update(Input input, float deltaTime, float timeToSwitch)
{
	vec2 moveDirection(0.0f, 0.0f);

	if (bounceTimer <= 0.0f) {
		if (playerNumber == 1)
		{
			if (input.isKeyDown('w')) {
				//move up
				moveDirection.y = 1.0f;
			}
			if (input.isKeyDown('s')) {
				//move down
				moveDirection.y = -1.0f;
			}
			if (input.isKeyDown('d')) {
				//move right
				moveDirection.x = 1.0f;
			}
			if (input.isKeyDown('a')) {
				//move left
				moveDirection.x = -1.0f;
			}
		}
		else if (playerNumber == 2)
		{
			if (input.isKeyDown('i')) {
				//move up
				moveDirection.y = 1.0f;
			}
			if (input.isKeyDown('k')) {
				//move down
				moveDirection.y = -1.0f;
			}
			if (input.isKeyDown('l')) {
				//move right
				moveDirection.x = 1.0f;
			}
			if (input.isKeyDown('j')) {
				//move left
				moveDirection.x = -1.0f;
			}
		}

		//normalize moveDirection so diagonal movement is not faster than axial movement
		moveDirection = normalize(moveDirection);
		moveDirection *= moveSpeed * deltaTime;

		playerModel.move(moveDirection);

		float distance = sqrt((moveDirection.x * moveDirection.x) + (moveDirection.y * moveDirection.y));
		this->distanceMoved += distance;
	}
	else {
		bounceTimer -= deltaTime;
		playerModel.move(bounceDirection * moveSpeed * deltaTime);
	}

	//keep player on screen
	if (playerModel.getPosition().x - playerModel.getRadius() < -1.0f) {
		playerModel.setPosition(-1.0f + playerModel.getRadius(), playerModel.getPosition().y);
	}
	else if (playerModel.getPosition().x + playerModel.getRadius() > 1.0f) {
		playerModel.setPosition(1.0f - playerModel.getRadius(), playerModel.getPosition().y);
	}
	if (playerModel.getPosition().y - playerModel.getRadius() < -1.0f) {
		playerModel.setPosition(playerModel.getPosition().x, -1.0f + playerModel.getRadius());
	}
	else if (playerModel.getPosition().y + playerModel.getRadius() > 1.0f) {
		playerModel.setPosition(playerModel.getPosition().x, 1.0f - playerModel.getRadius());
	}

	//rotate model
	if (timeToSwitch != 0) {
		this->playerModel.rotate(2.0f * deltaTime / timeToSwitch);
	}
	else {
		this->playerModel.rotate(2.0f * deltaTime);
	}
}

void Player::draw(GLuint program)
{
	playerModel.draw(program);

	int count = 0;
	for (auto *r : scoreCounters) {
		++count;
		if (count > score) {
			break;
		}
		r->draw(program);
	}
}

Circle Player::getModel()
{
	return this->playerModel;
}

void Player::onPlayerCollision(vec2 bounce)
{
	if (this->isPredator) {
		this->score++;
	}
	else {
		this->playerModel.changeRadius(this->playerModel.getRadius() * 0.75f);
	}

	bounceTimer = 0.5f;
	this->bounceDirection = bounce;
}

void Player::onObstacleCollision()
{
	if (this->isPredator) {
		float moveRemaining = this->movementBudget - this->distanceMoved;
		moveRemaining *= 0.75f;
		this->distanceMoved = this->movementBudget - moveRemaining;
	}
}

void Player::onOtherPlayerObstacleCollision()
{
	if (this->isPredator) {
		float moveRemaining = this->distanceMoved;
		moveRemaining *= 0.15f;
		this->distanceMoved -= moveRemaining;
	}
}

void Player::makePredator()
{
	this->distanceMoved = 0;
	this->getModel().makeJagged();
	this->isPredator = true;
}

void Player::makePrey()
{
	this->isPredator = false;
}

void Player::onRoleSwitch()
{
	this->playerModel.changeRadius(this->defaultRadius);
}

float Player::getDistanceMoved()
{
	return this->distanceMoved;
}

float Player::getMovementBudget()
{
	return this->movementBudget;
}

bool Player::isFrozen()
{
	return bounceTimer > 0;
}

bool Player::isOverMovementBudget()
{
	return (distanceMoved >= movementBudget);
}

int Player::getScore()
{
	return this->score;
}