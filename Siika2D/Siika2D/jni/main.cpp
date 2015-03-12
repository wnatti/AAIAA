#include "../Siika2D.h"
#include "../BufferManager.h"
#include "../engine/graphics/ShaderManager.h"

Siika2D *siika = Siika2D::UI();

graphics::BufferManager buffManager;
graphics::ShaderManager shaderManager;

bool done = false;

GLfloat vertices[] =
{
	0.5, 1.0, 1.0, 1.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 0.0, 1.0, 1.0, 1.0, 1.0
};

GLint indices[] =
{
	1, 2, 3,
	2, 3, 1
};


void drawStuff()
{
	
}

void doStuff()
{
	siika->clear();
	buffManager.addVertices(vertices, sizeof(vertices));
	buffManager.addIndices(indices, sizeof(indices));

	buffManager.setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::unknown);
	done = true;

	buffManager.draw();
	siika->swap();
}


void siika_main()
{
	
	if (siika->drawReady== true && done == false)
		doStuff();

}