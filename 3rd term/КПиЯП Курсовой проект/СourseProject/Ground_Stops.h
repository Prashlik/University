#pragma once
#include "Stops.h"
#include "Ground_Trans.h"
#include "Template.h"


class Ground_Stops : public Stops
{
private:

	Ring<class Ground_Trans*> buses;
	Ring<class Ground_Trans*> trams;
	Ring<class Ground_Trans*> trolleybuses;

public:

	Ground_Stops() : Stops() {};

	Ground_Stops(int i, string n, vector<Nearest_St> nr, Ring<class Ground_Trans*> bus, Ring<class Ground_Trans*> tram, Ring<class Ground_Trans*> trolleybus) : Stops(i, n, nr)
	{
		buses = bus;
		trams = tram;
		trolleybuses = trolleybus;
	}

	Ground_Stops(Ground_Stops& st)
	{
		Info = st.Info;
		buses = st.buses;
		trams = st.trams;
		trolleybuses = st.trolleybuses;
		nearest = st.nearest;
	}

	void settrans(int flag, Ring<class Ground_Trans*> trans);
	void pushtrans(int flag, Ground_Trans* trans);
	void setnstops(Ring<Ground_Stops>& gs);

	Ring<class Ground_Trans*> gettrans(int flag);

	void info();

	Ground_Stops& operator=(Ground_Stops& st);

	friend istream& operator>>(istream& stream, Ground_Stops& S);
	friend ostream& operator<<(ostream& stream, Ground_Stops& S);
	friend ifstream& operator>>(ifstream& stream, Ground_Stops& S);
	friend ofstream& operator<<(ofstream& stream, Ground_Stops& S);
};
