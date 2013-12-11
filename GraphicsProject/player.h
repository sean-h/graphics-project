/***********
* player.h
***********/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "input.h"
#include "shapes.h"
#include <vector>

class Player
{
private:
	int playerNumber;
	int score;
	
	float movementBudget;
	float distanceMoved;
	float moveSpeed;
	Circle playerModel;
	float bounceTimer;
	float collisionBounceTime;
	vec2 bounceDirection;
	bool isPredator;
	float defaultRadius;
	std::vector<Rect*> scoreCounters;
public:
	Player(int);
	void update(Input, float, float);
	void draw(GLuint);
	Circle getModel();
	void onPlayerCollision(vec2);
	void onObstacleCollision();
	void onOtherPlayerObstacleCollision();
	void makePredator();
	void makePrey();
	void onRoleSwitch();
	float getMovementBudget();
	float getDistanceMoved();
	bool isFrozen();
	bool isOverMovementBudget();
	int getScore();
};

#endif