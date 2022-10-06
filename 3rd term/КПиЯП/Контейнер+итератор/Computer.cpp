#include <cstring>
#include <string.h>
#include <cstdio>
#include "Computer.h"

void Computer::setyear()
{
	year = InInt(1950, 2020);
}

void Computer::setprice()
{
	price = InInt(100, 10000);
}

void Computer::setbrand()
{
	brand.clear();
	brand = InName();
}

void Computer::setname()
{
	name.clear();
	name = InString();
}

int Computer::getyear()
{
	return year;
}

double Computer::getprice()
{
	return price;
}

string Computer::getbrand()
{
	return brand;
}

string Computer::getname()
{
	return name;
}

void Computer::table()
{
	cout << setw(15) << "Brand" << '|' << setw(6) << "Year" << '|' << setw(15) << "Name" << '|' << setw(10) << "Price" << '|';
}

istream& operator>>(istream& stream, Computer& c)
{
	rewind(stdin);
	cout << "\nEnter the name of the brand: ";
	c.brand = InName();
	rewind(stdin);
	cout << "\nEnter the year of creation: ";
	c.year = InInt(1950, 2020);
	rewind(stdin);
	cout << "\nEnter the name of the computer: ";
	c.name = InString();
	rewind(stdin);
	cout << "\nEnter the price of the computer: ";
	c.price = InInt(100, 10000);

	return stream;
}

ostream& operator<<(ostream& stream, Computer& c)
{
	stream << setw(15) << c.brand << '|' << setw(6) << c.year << '|' << setw(15) << c.name << '|' << setw(10) << c.price << '|';

	return stream;
}