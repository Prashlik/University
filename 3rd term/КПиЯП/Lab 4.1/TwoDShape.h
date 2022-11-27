#pragma once
#include "TwoDShape.h"

class Triangle : public TwoDShape
{
	int x2, y2, z2;
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
