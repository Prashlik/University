#pragma once
#include "Transport.h"
#include "Underground_Stops.h"

class Underground_Trans : public Transport
{
protected:

	vector<class Underground_Stops*> stops;
	Time interval, winterval;

public:

	Underground_Trans()	{	}

	Underground_Trans(int num, Time t, Time wt, vector<int> s, vector<class Underground_Stops*> st) : Transport(num, s)
	{
		stops = st;
		interval = t;
		winterval = wt;
	}

	Underground_Trans(Underground_Trans& trans)
	{
		stops = trans.stops;
		number = trans.number;
		st = trans.st;
		interval = trans.interval;
		winterval = trans.winterval;
	}

	void setstops(vector<class Underground_Stops*> stops);
	void setinterval(Time t);
	void setwinterval(Time t);
	void info();
	void pushstops(class Underground_Stops* st);

	vector<class Underground_Stops*> getstops();
	Time getinterval();
	Time getwinterval();

	Underground_Trans& operator=(Underground_Trans& trans);
	bool operator>(Underground_Trans& T);
	bool operator<(Underground_Trans& T);

	friend istream& operator>>(istream& stream, Underground_Trans& T);
	friend ostream& operator<<(ostream& stream, Underground_Trans& T);
	friend ifstream& operator>>(ifstream& stream, Underground_Trans& T);
	friend ofstream& operator<<(ofstream& stream, Underground_Trans& T);
};