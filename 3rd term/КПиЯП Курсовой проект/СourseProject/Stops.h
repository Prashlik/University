#pragma once
#include "Company.h"
#include "Structs.h"
#include "Template.h"

class Stops : public Company
{
protected:
	
	StopsInfo Info;
	vector<Nearest_St> nearest;

public:

	Stops()
	{
		Info.id = 0;
		Info.name = '\0';
	}

	Stops(int i, string n, vector<Nearest_St> nr)
	{
		Info.id = i;
		Info.name = n;
		nearest = nr;
	}

	Stops(Stops& st)
	{
		Info = st.Info;
		Info.name = st.Info.name;
		nearest = st.nearest;
	}

	~Stops() {	}

	void setid(int i);
	void setname(string n);
	void setnstops(vector<Nearest_St> nr);
	void pushnstops(Nearest_St st);

	bool operator>(Stops& S);
	bool operator<(Stops& S);

	int getid();
	string getname();
	vector<Nearest_St> getnstops();

	Stops& operator=(Stops& st);

	friend istream& operator>>(istream& stream, Stops& S);
	friend ostream& operator<<(ostream& stream, Stops& S);
	friend ifstream& operator>>(ifstream& stream, Stops& S);
	friend ofstream& operator<<(ofstream& stream, Stops& S);
};
