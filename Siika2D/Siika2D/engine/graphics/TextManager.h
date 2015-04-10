#pragma once

#include "Text.h"
#include "ShaderManager.h"

namespace graphics
{
	/**
		Class for creating and drawing text.
	*/
	class TextManager
	{
	public:
		/**
			Constructor.
			Creates shader for drawing text.
		*/
		TextManager(core::ResourceManager* resourceManager, ShaderManager* shaderManager, glm::vec2 displaySize);
		~TextManager();

		/**
			Creates Text object and returns it.
		*/
		Text* createText();

		/**
			Draws all created Text objects that have been properly initialized.
		*/
		void drawTexts();

	private:
		/**
			Loads shaders from files.
			Vertex shader from "vertexTextShader.glsl" and fragment shader from "fragmentTextShader.glsl".
		*/
		Shader* createShaders();

		core::ResourceManager* _resourceManager;
		ShaderManager* _shaderManager;
		Shader* _textShader;
		std::vector<Text> _texts;
		glm::vec2 _displaySize;
	};
}