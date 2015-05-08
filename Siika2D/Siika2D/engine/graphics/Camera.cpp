#include "Camera.h"
using namespace graphics;

Camera::Camera(float x, float y) :_posX(x), _posY(y)
{
	_posX = _position.x;
	_posY = _position.y;

	initialize();
}

Camera::~Camera()
{

}

void Camera::initialize()
{
	Shader *shader;
	/**
	Initialize window projection matrix
	*/
	glUseProgram();
	windowProjection = glm::ortho(0, _screenWidth, _screenHeight, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, viewProjection);
	/**
	Pass to shaders
	*/
	glUniformMatrix4fv(shader->windowProjection, 1, false, "windowProjection");

	/**
	Initialize view projection matrix 
	*/
	viewProjection = glm::lookAt(
		glm::vec3(_position.x, _position.y, 2.0f), // Camera Position
		glm::vec3(_position.x, _position.y, 1.0f), // Where the camera looks
		glm::vec3(0, 1, 0));

	glGetFloatv(GL_MODELVIEW_MATRIX, viewProjection);

	glUniformMatrix4fv(shader->viewProjection, 1, false, "viewProjection");

	/**
	world translation
	*/
	worldProjection = glm::translate(worldProjection, glm::vec3(0.1f, 0.2f, 0.5f));
	glUniformMatrix4fv(shader->worldProjection, 1, false, "worldProjection");
	



	
}

void Camera::moveCamera(CAMERA_MOVEMENT move)
{
	switch (move)
	{
	case UP:

		break;
	
	case DOWN:

		break;
		
	case LEFT:

		break;

	case RIGHT:

		break;
	}
}

void Camera::setCameraPosition(glm::vec2 _position)
{

}


