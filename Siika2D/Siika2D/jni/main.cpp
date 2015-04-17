
#include "..\engine\core\Siika2D.h"
#include "../engine/graphics/BufferManager.h"
#include "../engine/graphics/ShaderManager.h"
#include "../engine/core/ResourceManager.h"
#include "../engine/graphics/SpriteManager.h"
#include "../engine/graphics/TextureManager.h"
#include "../engine/core/MemoryManager.h"
#include "../engine/audio/Audio.h"

core::Siika2D *siika = core::Siika2D::UI();

graphics::ShaderManager *shaderManager;
graphics::BufferManager *buffManager;
graphics::SpriteManager *spriteManager;
core::ResourceManager *resourceManager;
graphics::TextureManager * texMngr;

bool managersDone = false;
graphics::Sprite * sprite, *sprite2;
GLfloat vertices[] =
{
	-1.0, -1.0, 0.0, 0.0, 1.0, 1.0,
	0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
	1.0, -1.0, 0.0, 0.0, 1.0, 1.0,
	1.0, -1.0, 0.0, 0.0, 1.0, 1.0
};

GLint indices[] =
{
	//1, 2, 3
	1, 2, 4, 2, 3, 4
};
float pos = 0;
uint blue = 1;
uint green = 128;
void doStuff()
{
	
	if(!managersDone)
	{
		siika->GRAPHICS->setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::texture);
		siika->GRAPHICS->useShader(true, true);

		resourceManager = &siika->_resourceManager;
		spriteManager = new graphics::SpriteManager(siika->GRAPHICS, siika->GRAPHICS);
		texMngr = new graphics::TextureManager(resourceManager);
		graphics::Texture * tex = texMngr->createTexture("tekstuuri.png");
		sprite = spriteManager->createSprite(glm::vec2(0, 0), glm::vec2(0.5, 0.5), glm::vec2(0.2, 0.2), tex, glm::vec2(0, 1), glm::vec2(1, 0));
		
		siika->GRAPHICS->useDefaultShader(false, true);
		sprite2 = spriteManager->createSprite(glm::vec2(0.5, 0.5), glm::vec2(0.5, 0.5), glm::vec2(0.2, 0.2), tex, glm::vec2(1, 0), glm::vec2(0, 1));

		managersDone = true;
		glActiveTexture(GL_TEXTURE0);
		//Audio ad;
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
	sprite->setPosition(glm::vec2(pos, sprite->getPosition()->y));
	siika->GRAPHICS->clear();
	//siika->GRAPHICS->draw();
	spriteManager->drawSprites();
//	siika->GRAPHICS->draw();
	siika->GRAPHICS->swap();


}

void siika_main()
{
	doStuff();

}
