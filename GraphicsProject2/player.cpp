#include "player.h"
#include <math.h>

Player::Player(int playerNum)
{
	this->playerNumber = playerNum;
	this->playerModel = Sphere(vec3(0.0, 0.0, 10.0), 1, RED);
	this->disk = Sphere(vec3(0.0, 0.0, 10.0), 1.0, BLUE);
	this->disk.setScale(1.25, 1.25, 0.1);
	if (playerNum == 1) {
		makePredator();
	} else {
		this->playerModel.setPosition(-playerModel.getPosition());
		makePrey();
	}
	this->score = 0;
	this->moveSpeed = 20.0;
	this->movementBudget = 100.0f;
	this->distanceMoved = 0.0f;
	this->bounceTimer = 0.0f;
	this->collisionBounceTime = 0.5;
	this->defaultRadius = 1.0f;
	this->playBoundary = vec2(20.0, 20.0);
}

void Player::update(Input input, float deltaTime, float timeToSwitch)
{
	vec3 moveDirection(0.0f, 0.0f, 0.0f);

    if (bounceTimer <= 0.0f) {
        if (playerNumber == 1)
        {
            if (input.isKeyDown('w')) {
                //move up
                moveDirection.x = -1.0f;
            }
            if (input.isKeyDown('s')) {
                //move down
                moveDirection.x = 1.0f;
            }
            if (input.isKeyDown('d')) {
                //move right
                moveDirection.z = -1.0f;
            }
            if (input.isKeyDown('a')) {
                //move left
                moveDirection.z = 1.0f;
            }
        }
        else if (playerNumber == 2)
        {
            if (input.isKeyDown('i')) {
                //move up
                moveDirection.x = -1.0f;
            }
            if (input.isKeyDown('k')) {
                //move down
				moveDirection.x = 1.0f;
            }
            if (input.isKeyDown('l')) {
                //move right
                moveDirection.z = -1.0f;
            }
            if (input.isKeyDown('j')) {
                //move left
                moveDirection.z = 1.0f;
            }
        }

        //normalize moveDirection so diagonal movement is not faster than axial movement
        //moveDirection = normalize(moveDirection);
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
		if (playerModel.getPosition().x - playerModel.getRadius() < -playBoundary.x) {
			playerModel.setPosition(vec3(
				-playBoundary.x + playerModel.getRadius(),
				playerModel.getPosition().y,
				playerModel.getPosition().z));
        }
        else if (playerModel.getPosition().x + playerModel.getRadius() > playBoundary.x) {
				playerModel.setPosition(vec3(
				playBoundary.x - playerModel.getRadius(),
				playerModel.getPosition().y,
				playerModel.getPosition().z));
        }
		if (playerModel.getPosition().z - playerModel.getRadius() < -playBoundary.y) {
			playerModel.setPosition(vec3(
				playerModel.getPosition().x,
				playerModel.getPosition().y,
				-playBoundary.y + playerModel.getRadius()));
        }
        else if (playerModel.getPosition().z + playerModel.getRadius() > playBoundary.y) {
				playerModel.setPosition(vec3(
				playerModel.getPosition().x,
				playerModel.getPosition().y,
				playBoundary.x - playerModel.getRadius()));
        }

		this->disk.setPosition(this->getPosition());
		this->disk.rotate(0.0, 90 * deltaTime, 0.0);
		this->playerModel.rotate(0.0, 90 * deltaTime, 0.0);

        //rotate model
        /*if (timeToSwitch != 0) {
                this->playerModel.rotate(2.0f * deltaTime / timeToSwitch);
        }
        else {
                this->playerModel.rotate(2.0f * deltaTime);
        }*/
}

void Player::draw(mat4 mv, mat4 p, Light light)
{
	this->playerModel.draw(mv, p, light);
	this->disk.draw(mv, p, light);
}

Sphere Player::getModel()
{
	return this->playerModel;
}

void Player::onPlayerCollision(vec3 otherPlayerPos)
{
	bounceDirection = -normalize(otherPlayerPos - getPosition());
	bounceTimer = collisionBounceTime;

	if (!isPredator) {
		float newRadius = std::max(playerModel.getRadius() * 0.8f, 0.5f);
		playerModel.setRadius(newRadius);
	}
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
	this->isPredator = true;
}

void Player::makePrey()
{
	this->isPredator = false;
}

void Player::onRoleSwitch()
{
	this->isPredator = !isPredator;
}

float Player::getMovementBudget()
{
	return this->movementBudget;
}

float Player::getDistanceMoved()
{
	return this->distanceMoved;
}

bool Player::isFrozen()
{
	return (this->bounceTimer < this->collisionBounceTime);
}

bool Player::isOverMovementBudget()
{
	return (this->distanceMoved > this->movementBudget);
}

int Player::getScore()
{
	return this->score;
}

vec3 Player::getPosition()
{
	return playerModel.getPosition();
}

float Player::getRadius()
{
	return playerModel.getRadius();
}