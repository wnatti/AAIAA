
#include "..\engine\core\Siika2D.h"
#include "../engine/audio/Audio.h"

core::Siika2D *siika = core::Siika2D::UI();

bool stuffDone = false;
std::vector<graphics::Sprite*>spriteVector;
glm::vec2 position;
graphics::Texture * tex;

float pos = 0;
uint blue = 1;
uint green = 128;
void doStuff()
{

	if(!stuffDone)
	{
		tex = siika->_textureManager->createTexture("tekstuuri.png");
		siika->_shaderManager->useShader(true, true);
		for (int i = 0; i < 50; i++)
		{
			
			spriteVector.push_back(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(64, 64), glm::vec2(32,32), tex, glm::vec2(0, 0), glm::vec2(1, 1)));
		}
		//sprite2 = siika->_spriteManager->createSprite(glm::vec2(0.5, 0.5), glm::vec2(0.5, 0.5), glm::vec2(0.2, 0.2), tex, glm::vec2(0, 1), glm::vec2(1, 0));
		//sprite3 = siika->_spriteManager->createSprite(glm::vec2(0.0, 0.0), glm::vec2(64, 64), glm::vec2(0.2, 0.2), tex, glm::vec2(0, 1), glm::vec2(1, 0));
		stuffDone = true;
	}

	std::vector<int> keys = siika->_input->getDownKeys();
	
	for (int i = 0; i < keys.size(); i++)
	{
		s2d_info("%i",keys[i]);
	}

	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
	}

	for (int i = 0; i < siika->_input->sticksActive(); i++)
	{
		position += siika->_input->stickOrientation(i)._orientation;
	}
	
	green += 2;
	for (int i = 0; i < spriteVector.size(); i++)
		spriteVector[i]->setColor(graphics::Color(0, green-i*10, blue-i*10, 1));

	if(blue > 254)
		blue = 0;
	if(green > 252)
		green = 0;
	pos = pos + 0.01;
	if(pos > 1.0f)
		pos = -1.0;

	for (int i = 0; i < spriteVector.size();i++)
		spriteVector[i]->setPosition(glm::vec2(position.x+i, position.y+i*10));

	siika->_graphicsContext->clear(); // EBIN XD
	siika->_spriteManager->drawSprites();
	siika->_graphicsContext->swap();
}

void siika_main()
{
	doStuff();

}
