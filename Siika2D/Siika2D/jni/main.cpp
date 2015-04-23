
#include "..\engine\core\Siika2D.h"
#include "../engine/audio/Audio.h"

core::Siika2D *siika = core::Siika2D::UI();

bool managersDone = false;
graphics::Sprite * sprite, *sprite2;
glm::vec2 position;

float pos = 0;
uint blue = 1;
uint green = 128;
void doStuff()
{

	if(!managersDone)
	{
		siika->_shaderManager->useShader(true, true);
		graphics::Texture * tex = siika->_textureManager->createTexture("tekstuuri.png");
		sprite = siika->_spriteManager->createSprite(glm::vec2(0, 0), glm::vec2(0.5, 0.5), glm::vec2(0.2, 0.2), tex, glm::vec2(0, 1), glm::vec2(1, 0));
		
		siika->_shaderManager->useDefaultShader(false, true);
		sprite2 = siika->_spriteManager->createSprite(glm::vec2(0.5, 0.5), glm::vec2(0.5, 0.5), glm::vec2(0.2, 0.2), tex, glm::vec2(1, 0), glm::vec2(0, 1));

		managersDone = true;
		glActiveTexture(GL_TEXTURE0);
		//Audio ad;
	}

	std::vector<int> keys = siika->INPUT->getDownKeys();
	
	for (int i = 0; i < keys.size(); i++)
	{
		s2d_info("%i",keys[i]);
	}

	if (siika->INPUT->touchingScreen())
	{
		position = siika->INPUT->touchPositionCurrent(0);
		s2d_info("%f %f", position.x, position.y);
	}
	
	green += 2;
	sprite->setColor(graphics::Color(0, green, blue++, 255));
	if(blue > 254)
		blue = 0;
	if(green > 252)
		green = 0;
	pos = pos + 0.01;
	if(pos > 1.0f)
		pos = -1.0;

	sprite->setPosition(glm::vec2(position.x/635.f - 1, -position.y/360.f + 1));
	siika->_graphicsContext->clear();
	siika->_spriteManager->drawSprites();
	siika->_graphicsContext->swap();
}

void siika_main()
{
	doStuff();

}
