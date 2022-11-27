#include <cstring>
#include <string.h>
#include <cstdio>
#include "Triangle.h"

void Triangle::area()
{
	cout << "The area of this triangle is: " << a * b * 0.5;
}

void Triangle::show()
{
	cout << "\nThe name of the figure is Triangle.";

	cout << "\n The length of the figure is " << a;
	cout << "\n The high of the figure is " << b;

}