#include <cstring>
#include <string.h>
#include <cstdio>
#include "Desctop.h"

Desctop::Desctop() : Computer()
{
	sort = "Desctop";
	powersup = 0;
}

Desctop::Desctop(int yr, double pr, const char* br, const char* nm, int pow) : Computer(yr, pr, br, nm)
{
	sort = "Desctop";
	powersup = pow;
};

void Desctop::setpowersup()
{
	powersup = InInt(100, 500);
}

int Desctop::getpowersup()
{
	return powersup;
}

void Desctop::table()
{
	cout << setw(10) << "Sort" << '|';
	(dynamic_cast<Computer&> (*this)).table(); 
	cout << setw(15) << "Power suply" << '|';
}

istream& operator>>(istream& stream, Desctop& c)
{
	stream >> dynamic_cast<Computer&> (c);
	cout << "\nEnter the power suply of the computer: ";
	rewind(stdin);
	c.powersup = InInt(100, 500);

	return stream;
}

ostream& operator<<(ostream& stream, Desctop& c)
{
	stream << setw(10) << c.sort << '|' << dynamic_cast<Computer&> (c) << setw(15) << c.powersup << '|';

	return stream;
}

ifstream& operator>>(ifstream& stream, Desctop& c)
{
	stream >> dynamic_cast<Computer&> (c) >> c.powersup;

	return stream;
}
ofstream& operator<<(ofstream& stream, Desctop& c)
{
	stream << dynamic_cast<Computer&> (c) << ' ' << c.powersup;

	return stream;
}

fstream& operator<<(fstream& out, Desctop& c)
{
	out << dynamic_cast<Computer&> (c);

	out.write(reinterpret_cast<char*>(&c.powersup), sizeof(int));

	return out;
}
fstream& operator>>(fstream& in, Desctop& c)
{
	in >> dynamic_cast<Computer&> (c);

	in.read(reinterpret_cast<char*>(&c.powersup), sizeof(int));

	return in;
}