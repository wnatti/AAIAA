#include "../Siika2D.h"
#include "../BufferManager.h"
#include "../engine/graphics/ShaderManager.h"

Siika2D *siika = Siika2D::UI();

graphics::ShaderManager *shaderManager;
graphics::BufferManager *buffManager;
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
		shaderManager = new graphics::ShaderManager;
		buffManager = new graphics::BufferManager;
		buffManager->setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::unknown);
		shaderManager->useShader();

		buffManager->addVertices(vertices, sizeof(vertices));
		buffManager->addIndices(indices, sizeof(indices));

		managersDone = true;
	}

	siika->clear();

	
	
	buffManager->draw();
	siika->swap();
}


void siika_main()
{
	
	if (siika->drawReady == true)
		doStuff();

}