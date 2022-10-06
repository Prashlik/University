#include <cstring>
#include <string.h>
#include <cstdio>
#include "Parallelepiped.h"

void Parallelepiped::volume()
{
	cout << "The area of this parallelepiped is: " << a * b * c;
}

void Parallelepiped::show()
{
	cout << "\nThe name of the figure is Parallelepiped.";

	cout << "\n The length of the figure is " << a;
	cout << "\n The high of the figure is " << b;
	cout << "\n The width of the figure is " << c;

}