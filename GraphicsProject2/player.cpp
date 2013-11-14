#include "player.h"

Player::Player(int playerNum)
{
	this->playerNumber = playerNum;
	this->playerModel = Sphere(vec3(0.0, 0.0, 10.0), 1);
	if (playerNum == 2) {
		this->playerModel.setPosition(-playerModel.getPosition());
	}
	this->score = 0;
	this->moveSpeed = 20.0;
	this->collisionBounceTime = 2.0;
	this->playBoundary = vec2(10.0, 10.0);
	this->bounceTimer = 0.0f;
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
		/*if (playerModel.getPosition().x - playerModel.getRadius() < -playBoundary.x) {
			playerModel.setPosition(vec3(
				-playBoundary.x + playerModel.getRadius(),
				playerModel.getPosition().y,
				playerModel.getPosition().z));
        }*/
        /*else if (playerModel.getPosition().x + playerModel.getRadius() > 1.0f) {
                playerModel.setPosition(1.0f - playerModel.getRadius(), playerModel.getPosition().y);
        }
        if (playerModel.getPosition().z - playerModel.getRadius() < -1.0f) {
                playerModel.setPosition(playerModel.getPosition().x, -1.0f + playerModel.getRadius());
        }
        else if (playerModel.getPosition().z + playerModel.getRadius() > 1.0f) {
                playerModel.setPosition(playerModel.getPosition().x, 1.0f - playerModel.getRadius());
        }*/

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
}

Sphere Player::getModel()
{
	return this->playerModel;
}

void Player::onPlayerCollision(vec3 otherPlayerPos)
{

}

void Player::onObstacleCollision()
{

}

void Player::onOtherPlayerObstacleCollision()
{

}

void Player::makePredator()
{

}

void Player::makePrey()
{

}

void Player::onRoleSwitch()
{

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