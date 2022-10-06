#include <cstring>
#include <string.h>
#include <cstdio>
#include "Laptop.h"

Laptop::Laptop() : Portative()
{
	type = "Laptop";
	usb = 0;
}

Laptop::Laptop(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz, int nusb) : Portative(yr, pr, br, nm, bat, tm, sz)
{
	type = "Laptop";
	usb = nusb;
};

void Laptop::setusb(int nusb)
{
	usb = nusb;
}

int Laptop::getusb()
{
	return usb;
}

void Laptop::table()
{
	cout << setw(7) << "Type" << '|';
	(dynamic_cast<Portative&> (*this)).table();
	cout << setw(20) << "Number of USB ports" << '|';
}

istream& operator>>(istream& stream, Laptop& c)
{
	stream >> dynamic_cast<Portative&> (c);
	cout << "\nEnter number of USB ports: ";
	rewind(stdin);
	c.usb = InInt(1, 7);

	return stream;
}

ostream& operator<<(ostream& stream, Laptop& c)
{
	stream << setw(7) << c.type << '|' << dynamic_cast<Portative&> (c) << setw(20) << c.usb << '|';

	return stream;
}