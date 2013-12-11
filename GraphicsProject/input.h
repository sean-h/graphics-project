/***********
* input.h
***********/

#ifndef __INPUT_H__
#define __INPUT_H__

#include <vector>

class Input
{
private:
	std::vector<unsigned char> keysDown;
public:
	Input();
	bool isKeyDown(unsigned char key);
	void keyPressed(unsigned char key);
	void keyReleased(unsigned char key);
};

#endif