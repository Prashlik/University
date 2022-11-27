#include <iostream>
#include <cstdio>
#include <conio.h>
#include "Header.h"

using namespace std;

int main()
{
	float a, b, c;

	cout << "Enter the length and the high of the triangle:\n";
	cin >> a;
	cin >> b;

	Triangle tr(a, b);

	cout << "\n---------------------------\n";

	tr.area();
	tr.volume();
	tr.show();

	cout << "\n---------------------------\n";

	cout << "\n\nEnter the length and the high of the rectangle:\n";
	cin >> a;
	cin >> b;

	Rectangle rc(a, b);

	cout << "\n---------------------------\n";

	rc.area();
	rc.volume();
	rc.show();

	cout << "\n---------------------------\n";

	cout << "\n\nEnter the length, the high and the widh of the parellelepiped:\n";
	cin >> a;
	cin >> b;
	cin >> c;

	Parallelepiped par(a, b, c);

	cout << "\n---------------------------\n";

	par.area();
	par.volume();
	par.show();

	cout << "\n---------------------------\n";

	cout << "\n\nEnter the length, the high and the widh of the pyramid:\n";
	cin >> a;
	cin >> b;
	cin >> c;

	Pyramid pyr(a, b, c);

	cout << "\n---------------------------\n";

	pyr.area();
	pyr.volume();
	pyr.show();

	cout << "\n---------------------------\n";
}