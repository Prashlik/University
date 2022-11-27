#include <cstring>
#include <string.h>
#include <cstdio>
#include "Smartphone.h"

Smartphone::Smartphone() : Portative()
{
	type = "Laptop";
	camres = 0;
}

Smartphone::Smartphone(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz, int res) : Portative(yr, pr, br, nm, bat, tm, sz)
{
	type = "Laptop";
	camres = res;
};

void Smartphone::setcamres(int nusb)
{
	camres = nusb;
}

int Smartphone::getcamres()
{
	return camres;
}

void Smartphone::table()
{
	cout << setw(10) << "Type" << '|';
	(dynamic_cast<Portative&> (*this)).table();
	cout << setw(20) << "Camera resolution" << '|';
}

istream& operator>>(istream& stream, Smartphone& c)
{
	stream >> dynamic_cast<Portative&> (c);
	cout << "\nEnter the camera resolution: ";
	rewind(stdin);
	c.camres = InInt(3, 15);

	return stream;
}

ostream& operator<<(ostream& stream, Smartphone& c)
{
	stream << setw(10) << c.type << '|' << dynamic_cast<Portative&> (c) << setw(20) << c.camres << '|';

	return stream;
}