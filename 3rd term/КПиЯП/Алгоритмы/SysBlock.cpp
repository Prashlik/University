#include <cstring>
#include <string.h>
#include <cstdio>
#include <conio.h>
#include "SysBlock.h"

SysBlock::SysBlock() : Desctop()
{
	type = "System block";
	high = 0;
	weight = 0;
	motherboard = "\0";
}

SysBlock::SysBlock(int yr, double pr, const char* br, const char* nm, int pow, double hig, double wgh, string mtr) : Desctop(yr, pr, br, nm, pow)
{
	type = "System block";
	high = hig;
	weight = wgh;
	motherboard = mtr;
};

void SysBlock::setmotherboard()
{
	motherboard.clear();
	motherboard = InString();
}

void SysBlock::sethigh()
{
	high = InDouble(1, 200);
}

void SysBlock::setweight()
{
	weight = InDouble(1, 20);
}

string SysBlock::getmotherboard()
{
	return motherboard;
}

double SysBlock::gethigh()
{
	return high;
}

double SysBlock::getweight()
{
	return weight;
}

void SysBlock::table()
{
	cout << setw(15) << "Type" << '|';
	(dynamic_cast<Desctop&> (*this)).table();
	cout << setw(7) << "Weight" << '|';
	cout << setw(7) << "High" << '|';
	cout << setw(15) << "Motherboard" << '|';
}

istream& operator>>(istream& stream, SysBlock& c)
{
	stream >> dynamic_cast<Desctop&> (c);
	cout << "\nEnter the weight of the computer: ";
	rewind(stdin);
	c.weight = InDouble(1, 20);
	cout << "\nEnter the high of the computer: ";
	rewind(stdin);
	c.high = InDouble(1, 200);
	cout << "\nEnter the motherboard of the computer: ";
	rewind(stdin);
	c.motherboard = InString();

	return stream;
}

ostream& operator<<(ostream& stream, SysBlock& c)
{
	stream << setw(15) << c.type << '|' << dynamic_cast<Desctop&> (c) << setw(7) << c.weight << '|' << setw(7) << c.high << '|' << setw(15) << c.motherboard << '|';

	return stream;
}