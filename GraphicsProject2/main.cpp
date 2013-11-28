/***********
* main.cpp
***********/
#include "Angel.h"
#include "graphics.h"
#include "player.h"
#include "shapes.h"
#include "input.h"
#include <time.h>
#include "camera.h"
#include "vec.h"
#include <vector>
#include "obstacle.h"
#include "collision.h"
#include <random>

Camera *camera;
Player *player1;
Player *player2;
Player *predator;
Player *prey;
Cube *playField;
Cube *movementBar;
Light *light;
std::vector<Obstacle*> obstacles;
const int obstacleCount = 20;
int switchCounter = 3;
bool isPaused = false;
bool isGameOver = false;
Input input;
clock_t timer;
clock_t gameTimer;

enum KEYBOARD_CONTROL
{
    LIGHT = 0,
    CAMERA = 1,
};
int keyboardControl = LIGHT;

enum MENU_ITEMS
{
    LIGHTING_ENABLED,
    DIFFUSE_RED,
    DIFFUSE_BLUE,
    DIFFUSE_GREEN,
    DIFFUSE_WHITE,
    SPEC_RED,
    SPEC_BLUE,
    SPEC_GREEN,
    SPEC_WHITE,
    AMB_RED,
    AMB_BLUE,
    AMB_GREEN,
    AMB_WHITE,
};

void init()
{
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    camera = new Camera(vec3(40.0, 40.0, 0.0));
    
    player1 = new Player(1);
    player2 = new Player(2);
    predator = player1;
    prey = player2;

    light = new Light(point4(0.0, 1.0, 0.0, 1.0),
                      color4(0.2, 0.2, 0.2, 1.0),
                      color4(1.0, 1.0, 1.0, 1.0),
                      color4(1.0, 1.0, 1.0, 1.0));

    for (int i = 0; i < obstacleCount; i++) {
        float x = rand() % 40 - 20;
        float y = rand() % 10;
        float z = rand() % 40 - 20;
        float moveX = rand() % 20 - 10;
        float moveY = rand() % 20 - 10;
        float moveZ = rand() % 20 - 10;

        Obstacle *o = new Obstacle(vec3(x, y, z), vec3(moveX, moveY, moveZ));
        obstacles.push_back(o);
    }

    playField = new Cube(vec3(0.0, 0.0, 0.0), vec3(40.0, 0.1, 40.0));
    movementBar = new Cube(vec3(0.0f, 0.80f, 0.0f), vec3(0.25f, 0.1f, 0.25f));

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glClearColor( 0.5, 0.5, 0.5, 1.0 ); 

    timer = clock();
}

void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    mat4  mv = camera->getLookAt();
    mat4  p = camera->getPerspective();
    player1->draw(mv, p, *light);
    player2->draw(mv, p, *light);
    playField->draw(mv, p, *light);

    movementBar->draw();

    for (auto o : obstacles) {
        o->draw(mv, p, *light);
    }

    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
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
    case 'v':
        keyboardControl = (keyboardControl + 1) % 2;
        break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    input.keyReleased(key);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    camera->setAspect(GLfloat(width) / height);
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

        if (!isPaused && !isGameOver) {
            //update everything
            float timeToChange = 1.0f - (predator->getDistanceMoved() / predator->getMovementBudget());
            player1->update(input, deltaSeconds, timeToChange);
            player2->update(input, deltaSeconds, timeToChange);
            if (keyboardControl == CAMERA) {
                camera->update(input, deltaSeconds);
            } else if (keyboardControl == LIGHT) {
                light->update(input, deltaSeconds);
            }
            movementBar->setScaleX(timeToChange);
            for (auto o : obstacles) {
                if (o->getIsAlive()) {
                    o->update(deltaSeconds);
                }
            }

            //check player collisions
            if (collides(player1->getModel(), player2->getModel())) {
                player1->onPlayerCollision(player2->getPosition());
                player2->onPlayerCollision(player1->getPosition());
            }

            //check collision between obstacles and players
            for (auto o : obstacles) {
                if (o->getIsAlive()) {
                    if (collides(player1->getModel(), o->getModel())) {
                        player1->onObstacleCollision();
                        player2->onOtherPlayerObstacleCollision();
                        o->onPlayerCollision();
                    }
                    if (collides(player2->getModel(), o->getModel())) {
                        player2->onObstacleCollision();
                        player1->onOtherPlayerObstacleCollision();
                        o->onPlayerCollision();
                    }
                }
            }

            if (predator->isOverMovementBudget()) {
                changePlayerRoles();
            }
        }

        //update display
        glutPostRedisplay();
}

void menu(int item)
{
    switch (item)
    {
    case LIGHTING_ENABLED:
        light->isEnabled = ! light->isEnabled;
        break;

    case DIFFUSE_RED:
        light->diffuse = RED;
        break;
    case DIFFUSE_BLUE:
        light->diffuse = BLUE;
        break;
    case DIFFUSE_GREEN:
        light->diffuse = GREEN;
        break;
    case DIFFUSE_WHITE:
        light->diffuse = WHITE;
        break;

    case SPEC_RED:
        light->specular = RED;
        break;
    case SPEC_BLUE:
        light->specular = BLUE;
        break;
    case SPEC_GREEN:
        light->specular = GREEN;
        break;
    case SPEC_WHITE:
        light->specular = WHITE;
        break;

    case AMB_RED:
        light->ambient = RED / 5.0;
        light->ambient.w = 1.0;
        break;
    case AMB_BLUE:
        light->ambient = BLUE / 5.0;
        light->ambient.w = 1.0;
        break;
    case AMB_GREEN:
        light->ambient = GREEN / 5.0;
        light->ambient.w = 1.0;
        break;
    case AMB_WHITE:
        light->ambient = WHITE / 5.0;
        light->ambient.w = 1.0;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 1);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Graphics Project 2");
    
    glewExperimental = true;
    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyUp);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    int lightMenu, diffuse, specular, ambient, mainMenu;
    

    diffuse = glutCreateMenu(menu);
    glutAddMenuEntry("Red", DIFFUSE_RED);
    glutAddMenuEntry("Blue", DIFFUSE_BLUE);
    glutAddMenuEntry("Green", DIFFUSE_GREEN);
    glutAddMenuEntry("White", DIFFUSE_WHITE);
    
    specular = glutCreateMenu(menu);
    glutAddMenuEntry("Red", SPEC_RED);
    glutAddMenuEntry("Blue", SPEC_BLUE);
    glutAddMenuEntry("Green", SPEC_GREEN);
    glutAddMenuEntry("White", SPEC_WHITE);

    ambient = glutCreateMenu(menu);
    glutAddMenuEntry("Red", AMB_RED);
    glutAddMenuEntry("Blue", AMB_BLUE);
    glutAddMenuEntry("Green", AMB_GREEN);
    glutAddMenuEntry("White", AMB_WHITE);

    lightMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Lighting", LIGHTING_ENABLED);
    glutAddSubMenu("Diffuse", diffuse);
    glutAddSubMenu("Specular", specular);
    glutAddSubMenu("Ambient", ambient);

    mainMenu = glutCreateMenu(menu);
    glutAddSubMenu("Lighting", lightMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
