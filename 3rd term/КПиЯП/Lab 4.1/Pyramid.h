#pragma once
#include "ThreeDShape.h"

class Pyramid : public ThreeDShape
{
public:

	Pyramid(double length, double high, double width)
	{
		a = length;
		b = high;
		c = width;
	}

	~Pyramid() {};

	void volume();
	void show();
};