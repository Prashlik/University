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
	c.price = InDouble(100, 10000);

	return stream;
}

ostream& operator<<(ostream& stream, Computer& c)
{
	stream << setw(15) << c.brand << '|' << setw(6) << c.year << '|' << setw(15) << c.name << '|' << setw(10) << c.price << '|';

	return stream;
}

ifstream& operator>>(ifstream& stream, Computer& c)
{
	stream >> c.brand >> c.year >> c.name >> c.price;

	return stream;
}
ofstream& operator<<(ofstream& stream, Computer& c)
{
	stream << setw(10) << c.brand << setw(6) << c.year << setw(15) << c.name << setw(10) << c.price;

	return stream;
}

fstream& operator<<(fstream& out, Computer& c)
{
	size_t len;

	len = c.brand.length();
	out.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	out.write(c.brand.data(), len);

	len = c.name.length();
	out.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	out.write(c.name.data(), len);

	out.write(reinterpret_cast<char*>(&c.year), sizeof(int));
	out.write(reinterpret_cast<char*>(&c.price), sizeof(double));

	return out;
}
fstream& operator>>(fstream& in, Computer& c)
{
	size_t len;
	char* buf;

	in.read(reinterpret_cast<char*>(&len), sizeof(size_t));
	buf = new char[len + 1];
	in.read(buf, len);
	buf[len] = 0;
	c.brand = buf;
	delete[]buf;

	in.read(reinterpret_cast<char*>(&len), sizeof(size_t));
	buf = new char[len + 1];
	in.read(buf, len);
	buf[len] = 0;
	c.name = buf;
	delete[]buf;

	in.read(reinterpret_cast<char*>(&c.year), sizeof(int));
	in.read(reinterpret_cast<char*>(&c.price), sizeof(double));

	return in;
}