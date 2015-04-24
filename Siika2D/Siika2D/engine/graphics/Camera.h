#pragma once
#include <GLES\gl.h>
#include <glm.hpp>

namespace graphics
{
	enum CAMERA_MOVEMENT{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum ZOOM{
		ZOOM_IN,
		ZOOM_OUT
	};

	class Camera
	{
	public:
		void initialize();
		void moveCamera(CAMERA_MOVEMENT move, float cameraSpeed);
		void setCameraPosition(glm::vec2 _position);
		void zoomCamera(ZOOM zoom, GLfloat zoomFactor);
		Camera(glm::vec2 pos, GLfloat w, GLfloat h);

	private:
		GLfloat _screenWidth, _screenHeight;
		glm::vec2 _position;


//VANHA KAMERA TÄSSÄ KIVASTI. TÄMÄ SILTÄ VARALTA ETTÄ UUSI KAMERA ON PIPPELISTÄ

	//	/**
	//	get projection
	//	*/
	//	glm::mat4 getProjection();
	//	/**
	//	 Get camera and eye position
	//	*/
	//	glm::mat4 getView();
	//	/**
	//	Camera is move
	//	*/
	//	void moveCamera(Camera_Movement movement);
	//	/**
	//	Set camera position
	//	*/
	//	void setCameraPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	//	/**
	//	Set the speed of the camera
	//	*/
	//	void setCameraSpeed(GLfloat speed);
	//protected:
	//	Camera(GLfloat posX,  GLfloat posZ, GLfloat posY, GLfloat frontX, GLfloat frontY, GLfloat frontZ) :
	//		   _posX(posX),_posY(posY), _posZ(posZ), _frontX(frontX),_frontY(frontY),_frontZ(frontZ){};
	//	~Camera(){};

	//private:
	//	/**
	//	Calculates new front values 
	//	*/
	//	void updateCamera();

	//	glm::vec3 _cameraPos;
	//	glm::vec3 _front;
	//	glm::vec3 _up;
	//	GLfloat _cameraSpeed = 0.0f;
	//	GLfloat _posX, _posZ, _posY, _frontX, _frontY, _frontZ;
	}; 



}