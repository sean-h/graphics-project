#include "shapes.h"

Shape::Shape()
{ 
	program = InitShader("vshader53.glsl", "fshader42.glsl");
    glUseProgram(program);

	modelViewMat = glGetUniformLocation(program, "ModelView");
    projectionMat = glGetUniformLocation(program, "Projection");
	positionMat = glGetUniformLocation(program, "Position");
	scaleMat = glGetUniformLocation(program, "Scale");
	rotationMat = glGetUniformLocation(program, "Rotation");

	glGenBuffers(1, &buffer);
}

void Shape::setUpShader()
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * numVertices + sizeof(color4) * numVertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * numVertices, points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * numVertices, sizeof(vec3) * numVertices, normals);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vNormal = glGetAttribLocation(program, "vNormal"); 
    glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numVertices));		
}

void Shape::draw(mat4 mv, mat4 p, Light light)
{
	setUpShader();

	mat4 t = Translate(position);
	glUniformMatrix4fv(positionMat, 1, GL_TRUE, t);

	mat4 s = Scale(scale);
	glUniformMatrix4fv(scaleMat, 1, GL_TRUE, s);

	mat4 r = RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
	glUniformMatrix4fv(rotationMat, 1, GL_TRUE, r);

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, light.ambient * ambient);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, light.diffuse * diffuse);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, light.specular * specular);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light.position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
	glUniform1i(glGetUniformLocation(program, "LightingEnabled"), light.isEnabled);
	glUniform4fv(glGetUniformLocation(program, "Diffuse"), 1, diffuse);
	glUniformMatrix4fv(projectionMat, 1, GL_TRUE, p);
	glUniformMatrix4fv(modelViewMat, 1, GL_TRUE, mv);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

int Shape::getNumVertices()
{
	return numVertices;
}

void Shape::move(vec3 amount)
{
	this->position += amount;
}

vec3 Shape::getPosition()
{
	return this->position;
}

void Shape::setPosition(vec3 pos)
{
	this->position = pos;
}

void Shape::rotate(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}

void Shape::setColor(color4 color)
{
	diffuse = color;
}