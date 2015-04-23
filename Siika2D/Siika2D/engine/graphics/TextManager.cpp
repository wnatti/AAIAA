#include "TextManager.h"

using namespace graphics;


TextManager::TextManager(core::ResourceManager* resourceManager, ShaderManager* shaderManager, glm::vec2 displaySize)
{
	_resourceManager = resourceManager;
	_shaderManager = shaderManager;
	_displaySize = displaySize;

	_textShader = createShaders();
	_program = _textShader->getProgram();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


TextManager::~TextManager()
{

}


Text* TextManager::createText()
{
	_texts.push_back(Text(_resourceManager));
	return &_texts.at(_texts.size()-1);
}


void TextManager::drawTexts()
{
	GLint error = glGetError();
	s2d_assert(error == 0);

	Shader* previousShader =_shaderManager->getShader();
	_shaderManager->setCurrentShader(_textShader);
	glUseProgram(_program);

	error = glGetError();
	s2d_assert(error == 0);

	GLint textureSampler;
	GLuint texture;
	GLint positionLoc;

	setAttributes(positionLoc);
	setTextureUniform(textureSampler, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < _texts.size(); i++)
	{
		if (_texts.at(i).isInitialized)
		{
			setColorUniform(_texts.at(i).getColor());
			_texts.at(i).draw(_displaySize, positionLoc);
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	_shaderManager->setCurrentShader(previousShader);
}

Shader* TextManager::createShaders()
{
	GLint error = glGetError();
	s2d_assert(error == 0);

	Shader* previousShader = _shaderManager->getShader();
	Shader* textShader = _shaderManager->createShader("vertexTextShader.glsl", "fragmentTextShader.glsl");
	_shaderManager->setCurrentShader(previousShader);

	error = glGetError();
	s2d_assert(error == 0);

	return textShader;
}

void TextManager::setAttributes(GLint& positionLoc)
{
	GLint error = glGetError();
	s2d_assert(error == 0);

	positionLoc = glGetAttribLocation(_program, "coord");
	s2d_assert(!(positionLoc == -1));

	glEnableVertexAttribArray(positionLoc);

	//glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast <GLvoid*>(0));

	error = glGetError();
	s2d_assert(error == 0);
}

void TextManager::setColorUniform(Color color)
{
	GLint error = glGetError();
	s2d_assert(error == 0);

	GLint colorLoc = glGetUniformLocation(_program, "color");
	glm::vec4 glCol = color.getGLColor();
	GLfloat tempCol[4] = {glCol.r, glCol.g, glCol.b, glCol.a};
	glUniform4fv(colorLoc, 1, tempCol);

	error = glGetError();
	s2d_assert(error == 0);
}

void TextManager::setTextureUniform(GLint& textureSampler, GLuint& texture )
{
	GLint error = glGetError();
	s2d_assert(error == 0);

	textureSampler = glGetUniformLocation(_program, "tex");

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	error = glGetError();
	s2d_assert(error == 0);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	error = glGetError();
	s2d_assert(error == 0);

	glUniform1i(textureSampler, 0);
	error = glGetError();
	s2d_assert(error == 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	error = glGetError();
	s2d_assert(error == 0);
}