#pragma once
#include "Shape.h"

class TwoDShape : public Shape
{
protected:

	double a;

public:

	TwoDShape(double length)
	{
		a = length;
	};

	TwoDShape() 
	{
		a = 0;
	};
	~TwoDShape() {};

	virtual void show() = 0;
	virtual void area() = 0;
	virtual void volume() = 0;

};
