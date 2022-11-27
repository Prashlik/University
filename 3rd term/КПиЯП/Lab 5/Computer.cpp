#include <cstring>
#include <string.h>
#include <cstdio>
#include "Computer.h"

void Computer::setyear(int yr)
{
	year = yr;
}

void Computer::setprice(double pr)
{
	price = pr;
}

void Computer::setbrand(string br)
{
	brand.clear();
	brand = br;
}

void Computer::setname(string nm)
{
	name.clear();
	name = nm;
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
	stream >> c.brand;
	rewind(stdin);
	cout << "\nEnter the year of creation: ";
	stream >> c.year;
	rewind(stdin);
	cout << "\nEnter the name of the computer: ";
	stream >> c.name;
	rewind(stdin);
	cout << "\nEnter the price of the computer: ";
	stream >> c.price;

	return stream;
}

ostream& operator<<(ostream& stream, Computer& c)
{
	stream << setw(15) << c.brand << '|' << setw(6) << c.year << '|' << setw(15) << c.name << '|' << setw(10) << c.price << '|';

	return stream;
}