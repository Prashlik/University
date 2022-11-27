#pragma once
#include "ThreeDShape.h"

class Pyramid : public ThreeDShape
{
	double c;
	double Volume;
public:

	Pyramid(double length, double high, double width) : ThreeDShape(length, high)
	{
		c = width;

		Volume = a * b * c / 3;
	}

	Pyramid()
	{
		c = 0;

		Volume = 0;
	}

	~Pyramid() {};

	void volume() override;
	void show() override;
	void area() override
	{
		cout << "\nThere is no area for this figure";
	};
};