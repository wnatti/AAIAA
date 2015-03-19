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
		//shaderManager = new graphics::ShaderManager(&siika->_resourceManager);
		//buffManager = new graphics::BufferManager;
		//buffManager->setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::unknown);
		//shaderManager->useShader();

		//siika->addVertices(vertices, sizeof(vertices));
		//buffManager->addIndices(indices, sizeof(indices));

		managersDone = true;
	}

	siika->clear();

	
	
	//buffManager->draw();
	siika->swap();
}


void siika_main()
{
	
	if (siika->drawReady() == true)
		doStuff();

}