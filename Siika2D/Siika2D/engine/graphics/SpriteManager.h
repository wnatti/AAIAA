#pragma once
#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "Buffer.h"
#include "ShaderManager.h"
#include <map>
#include <algorithm>

namespace graphics
{

	class SpriteManager
	{
	public:
		SpriteManager(ShaderManager * shdrMngr) :_shdrMngr(shdrMngr){};
		~SpriteManager(){};
		Sprite * createSprite(){}
		void drawSprites();
	private:
		struct sprites_buffer
		{
			std::vector<Sprite> sprites;
			Buffer buffer;
		};
		
		void spriteBatcher(std::vector<Sprite> *toBatch);
		ShaderManager * _shdrMngr;
		std::map<Shader*, sprites_buffer> _sprites;
		/**
		Compares Z position between 2 sprites from the 'sprites' vector
		*/
		bool compareSpriteZs(Sprite &sprite1, Sprite &sprite2);
		/**
		Sorts sprites vector by comparing Z positions and textures
		*/
		vector<Sprite> *toBatch

	};
}