/***********
* main.cpp
***********/

#include "Angel.h"
#include "shapes.h"
#include "input.h"
#include "player.h"
#include "collision.h"
#include "obstacle.h"
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>

GLuint program;
Input input;
Player *player1, *player2, *predator, *prey;
clock_t timer;
clock_t gameTimer;
char text[80];

int predatorPlayer = 1;
bool isPaused = true;
bool isGameOver;
int switchCounter;
const int obstacleCount = 50;
std::vector<Obstacle*> obstacles;

Rect *movementBudget;

void newGame();
void changePlayerRoles();

void init()
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	
	//create players
	player1 = new Player(1);
	player2 = new Player(2);
	predator = player1;
	prey = player2;

	movementBudget = new Rect(vec2(-0.6f, 0.95f), vec2(0.6f, 0.9f), vec3(1.0f, 0.0f, 0.0f));

	newGame();
	changePlayerRoles();

	timer = clock();

    // Load shaders and use the resulting shader program
    program = InitShader("vshader24.glsl", "fshader24.glsl");
    glUseProgram(program);

	strcpy(text, "Hello, World!");

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glClearColor(0.5f, 0.5f, 0.5f, 1.0);
}

void newGame()
{
	obstacles.clear();

	player1->getModel().setPosition(vec2(-0.5f, 0.0f));
	player1->getModel().setPosition(vec2(0.5f, 0.0f));

	for (int i = 0; i < obstacleCount; ++i) {
		float randX = ((rand() % 200) - 100) / 100.0f;
		float randY = ((rand() % 200) - 100) / 100.0f;
		vec2 pos = vec2(randX, randY);
		if (getDistance(pos, player1->getModel().getPosition()) < 0.2f ||
			getDistance(pos, player2->getModel().getPosition()) < 0.2f) {
				continue;
		}

		Obstacle *obstacle = new Obstacle(pos);
		obstacles.push_back(obstacle);
	}

	isGameOver = false;
	switchCounter = 4;

	gameTimer = clock();
}

void changePlayerRoles()
{
	if (switchCounter == 0) {
		isGameOver = true;
	} else {
		Player *temp = predator;
		predator = prey;
		prey = temp;
	
		player1->onRoleSwitch();
		player2->onRoleSwitch();

		predator->makePredator();
		prey->makePrey();

		switchCounter--;
	}
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	//draw players
	player1->draw(program);
	player2->draw(program);

	//draw movement budget bar
	movementBudget->draw(program);

	//draw obstacles
	for (auto o : obstacles) {
		if (o->getIsAlive()) {
			o->draw(program);
		}
	}

	//player 1 score
	glRasterPos2f(-0.9f, 0.9f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)(std::to_string(player1->getScore()).c_str()));

	//player 2 score
	glRasterPos2f(0.9f, 0.9f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)(std::to_string(player2->getScore()).c_str()));

    glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
	input.keyPressed(key);

    switch (key) 
	{
	case VK_ESCAPE:
        exit(EXIT_SUCCESS);
        break;
	case VK_SPACE:
		isPaused = !isPaused;
		break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
	input.keyReleased(key);
}

void idle() 
{
	//handle timer
	clock_t deltaTime = clock() - timer;
	double deltaSeconds = (double)deltaTime / (double)CLOCKS_PER_SEC;
	if (deltaSeconds < 0.001) {
		Sleep (0.001 - deltaSeconds * 1000);
		deltaSeconds = 0.001;
	}
	timer = clock();

	//update players
	if (!isPaused && !isGameOver) {
		float timeToSwitch = 1 - (predator->getDistanceMoved() / predator->getMovementBudget());
		player1->update(input, (float)deltaSeconds, timeToSwitch);
		player2->update(input, (float)deltaSeconds, timeToSwitch);

		//update obstacles
		for (auto o : obstacles) {
			if (o->getIsAlive()) {
				o->update((float)deltaSeconds);

				//check collisions between obstacles and players
				if (circleCollision(player1->getModel(), o->getModel())) {
					player1->onObstacleCollision();
					o->onPlayerCollision();
					player2->onOtherPlayerObstacleCollision();
				}

				if (circleCollision(player2->getModel(), o->getModel())) {
					player2->onObstacleCollision();
					o->onPlayerCollision();
					player1->onOtherPlayerObstacleCollision();
				}
			}
		}

		//update movementBudget
		float movementBudgetPercentage = predator->getDistanceMoved() / predator->getMovementBudget();
		movementBudget->setWidth(1.2f - 1.2f * movementBudgetPercentage);

		//check collisions between players
		if (!predator->isFrozen()) {
			if (circleCollision(player1->getModel(), player2->getModel())) {
				vec2 bounceDirection = player1->getModel().getPosition() - player2->getModel().getPosition();
				bounceDirection = normalize(bounceDirection);
				player1->onPlayerCollision(bounceDirection);
				player2->onPlayerCollision(-bounceDirection);
			}
		}

		if (predator->isOverMovementBudget()) {
			changePlayerRoles();
		}
	}

	//update display
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(750, 750);
    
    glutInitContextVersion(3, 1);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutCreateWindow("Graphics Project");

	//required to run on desktop GPU
	glewExperimental = GL_TRUE;

    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}