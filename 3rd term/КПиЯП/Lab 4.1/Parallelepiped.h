#pragma once
#include "ThreeDShape.h"

class Parallelepiped : public ThreeDShape
{
public:

	Parallelepiped(double length, double high, double width)
	{
		a = length;
		b = high;
		c = width;
	}

	~Parallelepiped() {};

	void volume();
	void show();
};