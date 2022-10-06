#include <cstring>
#include <string.h>
#include <cstdio>
#include "Smartphone.h"

Smartphone::Smartphone() : Portative()
{
	type = "Smartphone";
	camres = 0;
}

Smartphone::Smartphone(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz, int res) : Portative(yr, pr, br, nm, bat, tm, sz)
{
	type = "Smartphone";
	camres = res;
};

void Smartphone::setcamres()
{
	camres = InInt(3, 15);
}

int Smartphone::getcamres()
{
	return camres;
}
string Smartphone::gettype()
{
	return type;
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

ifstream& operator>>(ifstream& stream, Smartphone& c)
{
	stream >> dynamic_cast<Portative&> (c);
	stream >> c.camres;

	return stream;
}
ofstream& operator<<(ofstream& stream, Smartphone& c)
{
	stream << dynamic_cast<Portative&> (c) << ' ' << c.camres;

	return stream;
}

fstream& operator<<(fstream& out, Smartphone& c)
{
	out << dynamic_cast<Portative&> (c);

	out.write(reinterpret_cast<char*>(&c.camres), sizeof(int));

	return out;
}
fstream& operator>>(fstream& in, Smartphone& c)
{
	in >> dynamic_cast<Portative&> (c);

	in.read(reinterpret_cast<char*>(&c.camres), sizeof(int));

	return in;
}