#pragma once
#include <GLES\gl.h>
#include <GLES2\gl2.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include "Shader.h"

namespace graphics
{
	enum CAMERA_MOVEMENT{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		void initialize();
		void moveCamera(CAMERA_MOVEMENT move);
		void setCameraPosition(glm::vec2 _position);

		/**
		Constructor takes vec2 object
		*/
		Camera(float x, float y);
		~Camera();

	private:
		int _screenWidth, _screenHeight;
		glm::vec2 _position, _origin;
		float _posX, _posY;
		glm::mat4 windowProjection, viewProjection, worldProjection;
	};
}


