#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdio>
#include "Portative.h"

Portative::Portative() : Computer()
{
	sort = "Portative";
	battery = 0;
	time = 0;
	screen = 0;
}

Portative::Portative(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz) : Computer(yr, pr, br, nm)
{
	sort = "Portative";
	battery = bat;
	time = tm;
	screen = sz;
};

void Portative::setbattery()
{
	battery = InInt(1000, 10000);
}

void Portative::settime()
{
	time = InInt(1, 25);
}

void Portative::setscreen()
{
	screen = InDouble(1, 20);
}

double Portative::getscreen()
{
	return screen;
}

int Portative::getbattery()
{
	return battery;
}

int Portative::gettime()
{
	return time;
}

void Portative::table()
{
	cout << setw(10) << "Sort" << '|';
	(dynamic_cast<Computer&> (*this)).table();
	cout << setw(10) << "Battery" << '|';
	cout << setw(12) << "Working time" << '|';
	cout << setw(15) << "Screen diagonal" << '|';
}

istream& operator>>(istream& stream, Portative& c)
{
	stream >> dynamic_cast<Computer&> (c);
	cout << "\nEnter the battery capacity: ";
	rewind(stdin);
	c.battery = InInt(1000, 10000);
	cout << "\nEnter the working time: ";
	rewind(stdin);
	c.time = InInt(1, 25);
	cout << "\nEnter the screen diagonal: ";
	rewind(stdin);
	c.screen = InDouble(1, 20);

	return stream;
}

ostream& operator<<(ostream& stream, Portative& c)
{
	stream << setw(10) << c.sort << '|' <<  dynamic_cast<Computer&> (c) << setw(10) << c.battery << '|' << setw(12) << c.time << '|' << setw(15) << c.screen << '|';

	return stream;
}