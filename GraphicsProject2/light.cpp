/***********
* light.cpp
***********/
#include "light.h"

Light::Light(point4 pos, color4 amb, color4 diff, color4 spec)
{
    this->position = pos;
    this->ambient = amb;
    this->diffuse = diff;
    this->specular = spec;
    this->isEnabled = true;
    this->moveSpeed = 10.0f;
}

void Light::update(Input input, float deltaTime)
{
    if (input.isKeyDown('t'))
    {
        move(vec3(-moveSpeed * deltaTime, 0.0f, 0.0f));
    }
    if (input.isKeyDown('g'))
    {
        move(vec3(moveSpeed * deltaTime, 0.0f, 0.0f));
    }

    if (input.isKeyDown('f'))
    {
        move(vec3(0.0, 0.0f, moveSpeed * deltaTime));
    }
    if (input.isKeyDown('h'))
    {
        move(vec3(0.0f, 0.0f, -moveSpeed * deltaTime));
    }

    if (input.isKeyDown('y'))
    {
        move(vec3(0.0, moveSpeed * deltaTime, 0.0f));
    }
    if (input.isKeyDown('r'))
    {
        move(vec3(0.0f, -moveSpeed * deltaTime, 0.0f));
    }
}

void Light::move(vec3 amount)
{
    this->position += amount;
}