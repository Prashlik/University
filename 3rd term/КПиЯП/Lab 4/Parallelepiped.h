#pragma once
#include "ThreeDShape.h"

class Parallelepiped : public ThreeDShape
{
	double c;
	double Volume;
public:

	Parallelepiped(double length, double high, double width)  : ThreeDShape(length, high)
	{
		c = width;

		Volume = a * b * c;
	}

	Parallelepiped()
	{
		c = 0;

		Volume = 0;
	}

	~Parallelepiped() {};

	void volume() override;
	void show() override;
	void area() override
	{
		cout << "\nThere is no area for this figure";
	};
};