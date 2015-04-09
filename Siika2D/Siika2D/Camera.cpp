#include "Camera.h"
using namespace graphics;


glm::mat4 Camera::getProjection()
{
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 1000.0f);
	return projection;
}

glm::mat4 Camera::getView()
{
	_cameraPos = glm::vec3(_posX, _posY, _posZ);
	_front = glm::vec3(_frontX, _frontY, _frontZ);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(_cameraPos, //Camera position
								 _cameraPos + _front, //Looking position
								 _up); //No camera rotation

	return view;

}


void Camera::moveCamera(Camera_Movement movement)
{
	if (movement == UP)
		_posY -= _cameraSpeed;
	else if (movement == DOWN)
		_posY += _cameraSpeed;
	else if (movement == RIGHT)
		_posX += _cameraSpeed;
	else if (movement == LEFT)
		_posX -= _cameraSpeed;
	else if (movement == ZOOM_IN)
		_posZ -= _cameraSpeed;
	else if (movement == ZOOM_OUT)
		_posZ += _cameraSpeed;
	else if (movement == ROTATE_CLOCKWISE)
		/*is code for rotate clockwise*/;
	else if (movement == ROTATE_COUNTER_CLOCKWISE)
		/*is code for rotate counter clockwise*/;
}

void Camera::setCameraPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
	posX = _posX;
	posY = _posY;
	posZ = _posZ;
	_cameraPos = glm::vec3(_posX, _posY, _posZ);
	updateCamera();
}

void Camera::setCameraSpeed(GLfloat speed)
{
	_cameraSpeed = speed;
}

void Camera::updateCamera()
{
	/*is code for updating front*/
}