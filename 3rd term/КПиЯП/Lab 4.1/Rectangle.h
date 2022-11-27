#pragma once
#include "TwoDShape.h"

class Rectangle : public TwoDShape
{
public:

	Rectangle(double length, double high)
	{
		a = length;
		b = high;
	}

	~Rectangle() {};

	void area();
	void show();
};
