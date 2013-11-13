//
// Perspective view of a color cube using LookAt() and Perspective()
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.
//

#include "Angel.h"
#include "graphics.h"
#include "cube.h"

Cube *cube;
Cube *cube2;

// Viewing transformation parameters

GLfloat radius = 1.0;
GLfloat theta = 0.0;
GLfloat phi = 0.0;

const GLfloat  dr = 5.0 * DegreesToRadians;

// Projection transformation parameters

GLfloat  fovy = 45.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect;       // Viewport aspect ratio
GLfloat  zNear = 0.1, zFar = 300.0;

// OpenGL initialization
void
init()
{
	GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	cube = new Cube(vec3(1.0, 0.0, 0.0));
	cube2 = new Cube(vec3(0.1, 0.1, 0.1));

	cube->setUpShader();
	cube2->setUpShader();

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    point4  eye( radius*sin(theta)*cos(phi), radius*sin(theta)*sin(phi), radius*cos(theta), 1.0 );
    point4  at( 0.0, 0.0, 0.0, 1.0 );
    vec4    up( 0.0, 1.0, 0.0, 0.0 );

    mat4  mv = LookAt( eye, at, up );
    mat4  p = Perspective( fovy, aspect, zNear, zFar );

	cube->draw(mv, p);
	cube2->draw(mv, p);
	
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;

	case 'z': zNear  *= 1.1; zFar *= 1.1; break;
	case 'Z': zNear *= 0.9; zFar *= 0.9; break;
	case 'r': radius *= 2.0; break;
	case 'R': radius *= 0.5; break;
	case 'o': theta += dr; break;
	case 'O': theta -= dr; break;
	case 'p': phi += dr; break;
	case 'P': phi -= dr; break;

	case ' ':  // reset values to their defaults
	    zNear = 0.5;
	    zFar = 3.0;

	    radius = 1.0;
	    theta  = 0.0;
	    phi    = 0.0;
	    break;
    }

    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );

    aspect = GLfloat(width)/height;
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Graphics Project 2" );
	
	glewExperimental = true;
    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );

    glutMainLoop();
    return 0;
}
