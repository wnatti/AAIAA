#pragma once
#include "..\glm\glm.hpp"
#include "..\glm\vec3.hpp"
#include <cstdlib>
#include <GLES\gl.h>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include "..\glm\gtc\matrix_transform.hpp"

namespace graphics
{
	enum Camera_Movement{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ZOOM_IN,
		ZOOM_OUT,
		ROTATE_CLOCKWISE,
		ROTATE_COUNTER_CLOCKWISE
	};

	class Camera
	{
	public:

		

		/**
		get projection
		*/
		glm::mat4 getProjection();
		/**
		 Get camera and eye position
		*/
		glm::mat4 getView();
		/**
		Camera is move
		*/
		void moveCamera(GLfloat _cameraSpeed, Camera_Movement movement);
		/**
		Set camera position
		*/
		void setCameraPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	protected:
		Camera(GLfloat posX, GLfloat posZ, GLfloat posY, GLfloat frontX, GLfloat frontY, GLfloat frontZ) :_posZ(posZ){};
		~Camera(){};

	private:
		/**
		Calculates new front values 
		*/
		void updateCamera();

		glm::vec3 _cameraPos;
		glm::vec3 _front;
		glm::vec3 _up;
		GLfloat _cameraSpeed = 0.0f;
		GLfloat _posX, _posZ, _posY, _frontX, _frontY, _frontZ;
	}; 



}