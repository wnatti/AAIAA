#include "../Siika2D.h"
#include "../engine/graphics/BufferManager.h"
#include "../engine/graphics/ShaderManager.h"

bool doneOnce = false;

core::Siika2D *siika = core::Siika2D::UI();


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
	
	if (!doneOnce)
	{
		siika->GRAPHICS->useShader();
		siika->GRAPHICS->setAttributes(graphics::shdrAtrib::position, graphics::shdrAtrib::color, graphics::shdrAtrib::unknown);

		siika->GRAPHICS->addVertices(vertices, sizeof(vertices));
		siika->GRAPHICS->addIndices(indices, sizeof(indices));

	
		doneOnce = !doneOnce;

		siika->INPUT->enableAccelerometer();
	}

	int i = 0;
	while (i < siika->INPUT->_accelerometerData.size())
	{
		s2d_info("%f %f %f", siika->INPUT->_accelerometerData[i].x, siika->INPUT->_accelerometerData[i].y, siika->INPUT->_accelerometerData[i].z);
		i++;
	}

	siika->GRAPHICS->clear();
	siika->GRAPHICS->draw();
	siika->GRAPHICS->swap();
}

void siika_main()
{

	doStuff();

}