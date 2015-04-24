#include "Camera.h"
using namespace graphics;

Camera::Camera(glm::vec2 pos, GLfloat w, GLfloat h)
{
	pos = _position;
	w = _screenWidth;
	h = _screenHeight;
	
}

void Camera::initialize()
{
	//set viewport
	glViewport(0.0f, 0.0f , _screenWidth, _screenHeight);

	//Initialize projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0.0f, _screenWidth, _screenHeight, 0.0, 1.0, -1.0);

	//initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Save default modelview matrix
	glPushMatrix();

}

void Camera::moveCamera(CAMERA_MOVEMENT move, float cameraSpeed)
{
	
	switch (move)
	{
	case UP:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glTranslatef(_position.x, (_position.y + cameraSpeed), 0.0f);
		break;

	case DOWN:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glTranslatef(_position.x, (_position.y - cameraSpeed), 0.0f);
		break;

	case LEFT:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glTranslatef((_position.x + cameraSpeed) , _position.y, 0.0f);
		break;		
	case RIGHT:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glTranslatef((_position.x - cameraSpeed), _position.y, 0.0f);		
		break;

	}
}

void Camera::setCameraPosition(glm::vec2 _position)
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(_position.x, _position.y, 0.0f);
}

void Camera::zoomCamera(ZOOM zoom, GLfloat zoomFactor)
{
	switch (zoom)
	{
	case ZOOM_IN:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glScalef(zoomFactor, zoomFactor, 0.0f);
		break;

	case ZOOM_OUT:
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glLoadIdentity();

		glScalef(-zoomFactor, -zoomFactor, 0.0f);
		break;
	}
}



//VANHA KAMERA TÄSSÄ KIVASTI. TÄMÄ SILTÄ VARALTA ETTÄ UUSI KAMERA ON PIPPELISTÄ

//glm::mat4 Camera::getProjection()
//{
//	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 1000.0f);
//	return projection;
//}
//
//glm::mat4 Camera::getView()
//{
//	_cameraPos = glm::vec3(_posX, _posY, _posZ);
//	_front = glm::vec3(_frontX, _frontY, _frontZ);
//	_up = glm::vec3(0.0f, 1.0f, 0.0f);
//
//	glm::mat4 view = glm::lookAt(_cameraPos, //Camera position
//								 _cameraPos + _front, //Looking position
//								 _up); //No camera rotation
//
//	return view;
//
//}
//
//
//void Camera::moveCamera(Camera_Movement movement)
//{
//	if (movement == UP)
//		_posY -= _cameraSpeed;
//	else if (movement == DOWN)
//		_posY += _cameraSpeed;
//	else if (movement == RIGHT)
//		_posX += _cameraSpeed;
//	else if (movement == LEFT)
//		_posX -= _cameraSpeed;
//	else if (movement == ZOOM_IN)
//		_posZ -= _cameraSpeed;
//	else if (movement == ZOOM_OUT)
//		_posZ += _cameraSpeed;
//	else if (movement == ROTATE_CLOCKWISE)
//		/*is code for rotate clockwise*/;
//	else if (movement == ROTATE_COUNTER_CLOCKWISE)
//		/*is code for rotate counter clockwise*/;
//}
//
//void Camera::setCameraPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
//{
//	posX = _posX;
//	posY = _posY;
//	posZ = _posZ;
//	_cameraPos = glm::vec3(_posX, _posY, _posZ);
//	updateCamera();
//}
//
//void Camera::setCameraSpeed(GLfloat speed)
//{
//	_cameraSpeed = speed;
//}
//
//void Camera::updateCamera()
//{
//	/*is code for updating front*/
//}