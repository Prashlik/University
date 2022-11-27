#pragma once
#include "Stops.h"

class Underground_Stops : public Stops
{
private:

	int line;

public:

	Underground_Stops() : Stops() { line = 0; }

	Underground_Stops(int i, string n, vector<Nearest_St> nr, int l) : Stops(i, n, nr)
	{
		line = l;
	}

	Underground_Stops(Underground_Stops& st)
	{
		Info = st.Info;
		line = st.line;
		nearest = st.nearest;
	}

	~Underground_Stops() {	}

	void setline(int l);
	void setnstops(Ring<Underground_Stops>& us);
	int getline();

	Underground_Stops& operator=(Underground_Stops& st);

	friend istream& operator>>(istream& stream, Underground_Stops& S);
	friend ostream& operator<<(ostream& stream, Underground_Stops& S);
	friend ifstream& operator>>(ifstream& stream, Underground_Stops& S);
	friend ofstream& operator<<(ofstream& stream, Underground_Stops& S);
};