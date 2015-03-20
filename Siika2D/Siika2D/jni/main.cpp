#include "../Siika2D.h"
#include "../engine/graphics/BufferManager.h"
#include "../engine/graphics/ShaderManager.h"

core::Siika2D *siika = core::Siika2D::UI();

bool managersDone = false;

GLfloat vertices[] =
{
	-1.0, -1.0, 1.0, 1.0, 1.0, 1.0,
	0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, -1.0, 1.0, 1.0, 1.0, 1.0
};

GLint indices[] =
{
	1, 2, 3
};


void doStuff()
{
	if (!managersDone)
	{
	
		siika->GRAPHICS->setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::unknown);
		siika->GRAPHICS->useShader();

		siika->GRAPHICS->addVertices(vertices, sizeof(vertices));
		siika->GRAPHICS->addIndices(indices, sizeof(indices));
		
		managersDone = true;
	}

	siika->GRAPHICS->clear();
	siika->GRAPHICS->draw();
	siika->GRAPHICS->swap();
}


void siika_main()
{
	
	if (siika->drawReady() == true)
		doStuff();

}