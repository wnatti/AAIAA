#include "TextManager.h"

using namespace graphics;


TextManager::TextManager(core::ResourceManager* resourceManager, ShaderManager* shaderManager, glm::vec2 displaySize)
{
	_resourceManager = resourceManager;
	_shaderManager = shaderManager;
	_textShader = createShaders();
	_displaySize = displaySize;
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
	Shader* previousShader =_shaderManager->getShader();
	_shaderManager->setCurrentShader(_textShader);

	for (int i = 0; i < _texts.size(); i++)
	{
		if (_texts.at(i).isInitialized)
			_texts.at(i).draw(_displaySize);
	}

	_shaderManager->setCurrentShader(previousShader);
}

Shader* TextManager::createShaders()
{
	return _shaderManager->createShader("vertexTextShader.glsl", "fragmentTextShader.glsl");
}