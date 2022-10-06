#pragma once
#include "Shape.h"

class ThreeDShape : public Shape
{
protected:

	double a, b, c;

public:

	virtual void show() = 0;
	virtual void volume() = 0;

};