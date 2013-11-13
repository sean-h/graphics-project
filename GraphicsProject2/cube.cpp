#include "cube.h"

Cube::Cube(vec3 pos)
{
	numVertices = 36;
	quadIndex = 0;
	position = pos;

	vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );
    vertices[4] = point4( -0.5, -0.5, -0.5, 1.0 );
    vertices[5] = point4( -0.5,  0.5, -0.5, 1.0 );
    vertices[6] = point4(  0.5,  0.5, -0.5, 1.0 );
    vertices[7] = point4(  0.5, -0.5, -0.5, 1.0 );

	vertex_colors[0] = color4( 0.0, 0.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 1.0, 0.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[3] = color4( 0.0, 1.0, 0.0, 1.0 );
    vertex_colors[4] = color4( 0.0, 0.0, 1.0, 1.0 );
    vertex_colors[5] = color4( 1.0, 0.0, 1.0, 1.0 );
    vertex_colors[6] = color4( 1.0, 1.0, 1.0, 1.0 );
    vertex_colors[7] = color4( 0.0, 1.0, 1.0, 1.0 );

	colorcube();
}

void Cube::setUpShader()
{
	glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

	program = InitShader( "vshader42.glsl", "fshader42.glsl" );
    glUseProgram( program );

    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );	

	modelViewMat = glGetUniformLocation( program, "model_view" );
    projectionMat = glGetUniformLocation( program, "projection" );
	positionMat = glGetUniformLocation(program, "pos");
}

void Cube::colorcube()
{
	quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

void Cube::quad(int a, int b, int c, int d)
{
	colors[quadIndex] = vertex_colors[a]; points[quadIndex] = vertices[a]; quadIndex++;
    colors[quadIndex] = vertex_colors[b]; points[quadIndex] = vertices[b]; quadIndex++;
    colors[quadIndex] = vertex_colors[c]; points[quadIndex] = vertices[c]; quadIndex++;
    colors[quadIndex] = vertex_colors[a]; points[quadIndex] = vertices[a]; quadIndex++;
    colors[quadIndex] = vertex_colors[c]; points[quadIndex] = vertices[c]; quadIndex++;
    colors[quadIndex] = vertex_colors[d]; points[quadIndex] = vertices[d]; quadIndex++;
}

void Cube::draw(mat4 mv, mat4 p)
{
	mat4 t = Translate(position);
	glUniformMatrix4fv(positionMat, 1, GL_TRUE, t);
	glUniformMatrix4fv( projectionMat, 1, GL_TRUE, p );
	glUniformMatrix4fv( modelViewMat, 1, GL_TRUE, mv );

	glDrawArrays( GL_TRIANGLES, 0, numVertices);
}

int Cube::getNumVertices()
{
	return numVertices;
}