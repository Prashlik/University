#include "Stops.h"

void Stops::setid(int i)
{
	Info.id = i;
}
void Stops::setname(string n)
{
	Info.name = n;
}
void Stops::setnstops(vector<Nearest_St> gs)
{
	nearest = gs;
}
void Stops::pushnstops(Nearest_St st)
{
	nearest.push_back(st);
}

int Stops::getid()
{
	return Info.id;
}
string Stops::getname()
{
	return Info.name;
}
vector<Nearest_St> Stops::getnstops()
{
	return nearest;
}

bool Stops::operator>(Stops& S)
{
	if (getname() > S.getname())
		return 1;
	return 0;
}
bool Stops::operator<(Stops& S)
{
	if (getname() < S.getname())
		return 1;
	return 0;
}

Stops& Stops::operator=(Stops& st)
{
	Info = st.Info;
	Info.name = st.Info.name;
	nearest = st.nearest;

	return *this;
}

istream& operator>>(istream& stream, Stops& S)
{
	cout << "\nEnter the name of the station: ";
	S.Info.name = InString();

	return stream;
}
ostream& operator<<(ostream& stream, Stops& S)
{
	stream << S.Info.name << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Stops& S)
{
	stream << setw(5) << S.Info.id;
	return stream;
}
ifstream& operator>>(ifstream& stream, Stops& S)
{
	stream >> S.Info.id;
	return stream;
}