/***********
* input.cpp
***********/
#include <vector>
#include "input.h"
#include <iostream>

Input::Input() { }

bool Input::isKeyDown(unsigned char key)
{
    for (auto i : keysDown) {
        if (i == key) {
            return true;
        }
    }

    return false;
}

void Input::keyPressed(unsigned char key)
{
    if (!isKeyDown(key)) {
        keysDown.push_back(key);
    }
}

void Input::keyReleased(unsigned char key)
{
    for (auto i = keysDown.begin(); i != keysDown.end(); ++i) {
        if (*i == key) {
            keysDown.erase(i);
            break;
        }
    }
}