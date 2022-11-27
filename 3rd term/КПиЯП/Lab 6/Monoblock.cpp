#include <cstring>
#include <string.h>
#include <cstdio>
#include "Monoblock.h"

Monoblock::Monoblock() : Desctop()
{
	type = "Monoblock";
	screen = 0;
}

Monoblock::Monoblock(int yr, double pr, const char* br, const char* nm, int pow, double scr, double wgh, string mtr) : Desctop(yr, pr, br, nm, pow)
{
	type = "Monoblock";
	screen = scr;
};

void Monoblock::setscreen(float hig)
{
	screen = hig;
}

double Monoblock::getscreen()
{
	return screen;
}

void Monoblock::table()
{
	cout << setw(15) << "Type" << '|';
	(dynamic_cast<Desctop&> (*this)).table();
	cout << setw(15) << "Screen diagonal" << '|';
}

istream& operator>>(istream& stream, Monoblock& c)
{
	stream >> dynamic_cast<Desctop&> (c);
	cout << "\nEnter the screen diagonal: ";
	rewind(stdin);
	c.screen = InDouble(1, 20);

	return stream;
}

ostream& operator<<(ostream& stream, Monoblock& c)
{
	stream << setw(15) << c.type << '|' << dynamic_cast<Desctop&> (c) << setw(15) << c.screen << '|';

	return stream;
}