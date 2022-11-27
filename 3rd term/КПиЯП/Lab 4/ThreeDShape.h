#pragma once
#include "Shape.h"

class ThreeDShape : public Shape
{
protected:

	double a, b;

public:

	ThreeDShape() 
	{
		a = 0;
		b = 0;
	};

	ThreeDShape(double length, double high)
	{
		a = length;
		b = high;
	};

	~ThreeDShape() {};

	virtual void show() = 0;
	virtual void volume() = 0;
	virtual void area() = 0;

};