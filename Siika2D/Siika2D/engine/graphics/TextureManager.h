#pragma once

#include "../core/ResourceManager.h"
#include "Texture.h"

namespace graphics
{
	class TextureManager;
}

class graphics::TextureManager
{
public:
	TextureManager(core::ResourceManager* resourceManager);
	~TextureManager();
	Texture* createTexture(std::string filename);

private:
	core::ResourceManager* _resourceManager;
	std::map<std::string, Texture> _createdTextures;
};