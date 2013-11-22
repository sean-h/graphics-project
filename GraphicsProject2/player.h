/***********
* player.h
***********/
#pragma once

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
    Sphere playerModel;
	Sphere disk;
    float bounceTimer;
    float collisionBounceTime;
    vec3 bounceDirection;
    bool isPredator;
    float defaultRadius;
	vec2 playBoundary;
	float jumpHeight;
	float jumpTimer;
	float jumpDuration;
	float jumpDamp;
	float jumpFrequency;
	std::vector<Cube *> scoreIndicators;
public:
	Player(int playerNum);
    void update(Input input, float deltaTime, float timeToSwitch);
    void draw(mat4 mv, mat4 p, Light light);
    Sphere getModel();
    void onPlayerCollision(vec3 otherPlayerPos);
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
	vec3 getPosition();
	float getRadius();
};