//
// Perspective view of a color cube using LookAt() and Perspective()
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.
//

#include "Angel.h"
#include "graphics.h"
#include "player.h"
#include "shapes.h"
#include "input.h"
#include <time.h>
#include "camera.h"
#include "vec.h"

Camera *camera;
Player *player1;
Player *player2;
Cube *playField;
Light *light;

bool isPaused = false;
bool isGameOver = false;
Input input;
clock_t timer;
clock_t gameTimer;

// OpenGL initialization
void init()
{
	GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	camera = new Camera(vec3(40.0, 40.0, 0.0));
	
	player1 = new Player(1);
	player2 = new Player(2);
	light = new Light(point4(-1.0, 1.0, 0.0, 1.0),
					  color4(0.2, 0.2, 0.2, 1.0),
					  color4(1.0, 1.0, 1.0, 1.0),
					  color4(1.0, 1.0, 1.0, 1.0));

	playField = new Cube(vec3(0.0, 0.0, 0.0), vec3(40.0, 0.1, 40.0));

    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
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
			light->position = player1->getModel().getPosition();
			light->position.y = 10;
			player1->update(input, deltaSeconds, 0);
			player2->update(input, deltaSeconds, 0);
			camera->update(input, deltaSeconds);

			vec3 d = player1->getPosition() - player2->getPosition();
			float r = player1->getRadius() + player2->getRadius();
			if (length(d) <= r)
			{
				player1->onPlayerCollision(player2->getPosition());
				player2->onPlayerCollision(player1->getPosition());
			}
        }

        //update display
        glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 2);
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

    glutMainLoop();
    return 0;
}
