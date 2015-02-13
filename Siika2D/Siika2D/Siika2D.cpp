#include "Siika2D.h"

Siika2D* Siika2D::_instance = nullptr;

Siika2D* Siika2D::getInstance()
{

	if (_instance == nullptr)
	{
		_instance = new Siika2D();

	}
	return _instance;

}

Siika2D::Siika2D()
{

}
