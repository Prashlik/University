#pragma once
#include "TwoDShape.h"

class Rectangle : public TwoDShape
{
	double b;
	double Perimeter, Area;
public:

	Rectangle(double length, double high) : TwoDShape(length)
	{
		b = high;

		Area = a * b;
		Perimeter = (a + b) * 2;
	}

	Rectangle()
	{
		a = 0;
		b = 0;

		Area = 0;
		Perimeter = 0;
	}

	~Rectangle() {};

	void area() override;
	void show() override;
	void volume() override
	{
		cout << "\nThere is no volume for this figure";
	};
};
