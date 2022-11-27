#include <cstring>
#include <string.h>
#include <cstdio>
#include "Pyramid.h"

void Pyramid::volume()
{
	cout << "The area of this pyramid is: " << a * b * c * 1 / 3;
}

void Pyramid::show()
{
	cout << "\nThe name of the figure is Pyramid.";

	cout << "\n The length of the figure is " << a;
	cout << "\n The high of the figure is " << b;
	cout << "\n The width of the figure is " << c;

}