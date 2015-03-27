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


void Camera::moveCamera(GLfloat _cameraSpeed, Camera_Movement movement)
{
	if (movement == UP)
		/*is code for up*/;
	if (movement == DOWN)
		/*is code for down*/;
	if (movement == RIGHT)
		/*is code for right*/;
	if (movement == LEFT)
		/*is code for left*/;
	if (movement == ZOOM_IN)
		/*is code for zoom in*/;
	if (movement == ZOOM_OUT)
		/*is code for zoom out*/;
	if (movement == ROTATE_CLOCKWISE)
		/*is code for rotate clockwise*/;
	if (movement == ROTATE_COUNTER_CLOCKWISE)
		/*is code for rotate counter clockwise*/;
}

void Camera::setCameraPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
	posX = _posX;
	posY = _posY;
	posZ = _posZ;
	_cameraPos = glm::vec3(_posX, _posY, _posZ);
	updateCamera()
}

void Camera::updateCamera()
{
	/*is code for updating front*/
}