#include <cstring>
#include <string.h>
#include <cstdio>
#include "Rectangle.h"

void Rectangle::area()
{
	cout << "The area of this rectangle is: " << a * b;
}

void Rectangle::show()
{
	cout << "\nThe name of the figure is Rectangle.";

	cout << "\n The length of the figure is " << a;
	cout << "\n The high of the figure is " << b;

}