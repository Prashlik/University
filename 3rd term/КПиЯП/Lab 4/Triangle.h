#pragma once
#include "TwoDShape.h"

class Triangle : public TwoDShape
{
	double b;
	double Area;
public:

	Triangle(double length, double high) : TwoDShape(length)
	{
		b = high;

		Area = a * b * 0.5;
	}

	Triangle()
	{
		b = 0;

		Area = 0;
	}

	~Triangle() {};

	void area() override;
	void show() override;
	void volume() override
	{
		cout << "\nThere is no volume for this figure";
	};
};
