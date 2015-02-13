#include "Color.h"

using namespace graphics;

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
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

void Color::setRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	_red = red / 255.f;
	_green = green / 255.f;
	_blue = blue / 255.f;
	_alpha = alpha / 255.f;
}

void Color::setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	_red = red / 255.f;
	_green = green / 255.f;
	_blue = blue / 255.f;
}

void Color::setAlpha(uint8_t alpha)
{
	_alpha = alpha / 255.f;
}

uint8_t Color::getR()
{
	return uint8_t(_red * 255);
}

uint8_t Color::getG()
{
	return uint8_t(_green * 255);
}

uint8_t Color::getB()
{
	return uint8_t(_blue * 255);
}

uint8_t Color::getA()
{
	return uint8_t(_alpha * 255);
}