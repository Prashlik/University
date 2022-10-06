#include <iostream>
#include <cstdio>
#include <conio.h>
#include "Triangle.h"
#include "Rectangle.h"
#include "Pyramid.h"
#include "Parallelepiped.h"

using namespace std;

int main()
{
	float a, b, c;

	cout << "Enter the length and the high of the triangle:\n";
	cin >> a;
	cin >> b;

	Triangle tr(a, b);

	tr.area();
	tr.show();

	cout << "\n\nEnter the length and the high of the rectangle:\n";
	cin >> a;
	cin >> b;

	Rectangle rc(a, b);

	rc.area();
	rc.show();

	cout << "\n\nEnter the length, the high and the widh of the parellelepiped:\n";
	cin >> a;
	cin >> b;
	cin >> c;

	Parallelepiped par(a, b, c);

	par.volume();
	par.show();

	cout << "\n\nEnter the length, the high and the widh of the pyramid:\n";
	cin >> a;
	cin >> b;
	cin >> c;

	Pyramid pyr(a, b, c);

	pyr.volume();
	pyr.show();
}