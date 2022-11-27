#pragma once
#include <iostream>
using namespace std;

class Shape
{
public:

	Shape() {};
	~Shape() {};

	virtual void show() = 0;
	virtual void area() = 0;
	virtual void volume() = 0;


};