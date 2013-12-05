/***********
* obstacle.h
***********/
#pragma once

#include "shapes.h"
#include "graphics.h"

class Obstacle
{
private:
    bool isAlive;
    Sphere* model;
    vec3 moveDirection;
    float hover;
    vec2 playBoundary;
public:
    Obstacle(vec3 pos, vec3 move);
    ~Obstacle();
    void update(float deltaTime);
    void draw(mat4 mv, mat4 p, Light light);
    void onPlayerCollision();
    Sphere* getModel();
    bool getIsAlive();
};