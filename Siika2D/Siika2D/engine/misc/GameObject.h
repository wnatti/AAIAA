#pragma once

#include "../graphics/SpriteManager.h"

class GameObject
{
public:
	GameObject(graphics::Sprite* sprite);
	~GameObject();

	void move(GLfloat x, GLfloat y);
	//void rotate(GLfloat rotation);
	
	graphics::Sprite* _sprite;
};