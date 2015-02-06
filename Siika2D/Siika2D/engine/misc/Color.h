#pragma once

/**
	Enumerators for basic colors:
	RED, GREEN, BLUE
*/
enum COLOR
{
	RED , GREEN, BLUE
};

namespace s2d
{
	class Color;
}

/**
	Basic color, 4 channels RGBA.
	Values are given in 0-255 format and stored internally as floats between 0-1.

	Enums for basic colors.
*/
class s2d::Color
{
public:

	/**
		Constructor.
		Set RGBA color values between 0-255. 
		Default value for alpha = 255.
	*/
	Color(int red, int green, int blue, int alpha = 255);

	/**
		Constructor.
		Set RGBA color values according to color enum.
	*/
	Color(COLOR color);
	~Color();

	/**
		Set RGBA color values according to color enum.
	*/
	void setColor(COLOR color);

	/**
		Set RGBA color values between 0-255.
	*/
	void setRGBA(int red, int green, int blue, int alpha);

	/**
		Set RGB color values between 0-255.
	*/
	void setRGB(int red, int green, int blue);

	/**
		Set alpha channel value between 0-255.
	*/
	void setAlpha(int alpha);

	/**
		Returns red channel value
	*/
	int getR();

	/**
		Returns green channel value
	*/
	int getG();

	/**
		Returns blue channel value
	*/
	int getB();

	/**
		Returns alpha channel value
	*/
	int getA();

private:
	float _red, _green, _blue, _alpha;

};