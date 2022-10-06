#pragma once
#include "TwoDShape.h"

class Triangle : public TwoDShape
{
public:

	Triangle(double length, double high)
	{
		a = length;
		b = high;
	}

	~Triangle() {};

	void area();
	void show();
};
