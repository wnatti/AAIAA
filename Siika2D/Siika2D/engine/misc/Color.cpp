#include "Color.h"

Color::Color(int red, int green, int blue, int alpha)
{
	_red = red / 255.f;
	_green = green / 255.f;
	_blue = blue / 255.f;
	_alpha = alpha / 255.f;
}

Color::Color(COLOR color)
{
	switch (color)
	{
	case RED:
		_red = 1.0f;
		_green = 0.0f;
		_blue = 0.0f;
		_alpha = 1.0f;
		break;
	case GREEN:
		_red = 0.0f;
		_green = 1.0f;
		_blue = 0.0f;
		_alpha = 1.0f;
		break;
	case BLUE:
		_red = 0.0f;
		_green = 0.0f;
		_blue = 1.0f;
		_alpha = 1.0f;
		break;
	}
}

Color::~Color()
{

}

void Color::setColor(COLOR color)
{
	switch (color)
	{
	case RED:
		_red = 1.0f;
		_green = 0.0f;
		_blue = 0.0f;
		_alpha = 1.0f;
		break;
	case GREEN:
		_red = 0.0f;
		_green = 1.0f;
		_blue = 0.0f;
		_alpha = 1.0f;
		break;
	case BLUE:
		_red = 0.0f;
		_green = 0.0f;
		_blue = 1.0f;
		_alpha = 1.0f;
		break;
	}
}

void Color::setRGBA(int red, int green, int blue, int alpha)
{
	_red = red / 255.f;
	_green = green / 255.f;
	_blue = blue / 255.f;
	_alpha = alpha / 255.f;
}

void Color::setRGB(int red, int green, int blue)
{
	_red = red / 255.f;
	_green = green / 255.f;
	_blue = blue / 255.f;
}

void Color::setAlpha(int alpha)
{
	_alpha = alpha / 255.f;
}

int Color::getR()
{
	return int(_red * 255);
}

int Color::getG()
{
	return int(_green * 255);
}

int Color::getB()
{
	return int(_blue * 255);
}

int Color::getA()
{
	return int(_alpha * 255);
}
