#pragma once
#include "Transport.h"
#include "Ground_Stops.h"
#include "Template.h"

using namespace std;

class Ground_Trans : public Transport
{
protected:

	Ring<class Ground_Stops*> stops;
	vector<Time> time1, time2;
	vector<Time> wtime1, wtime2;

public:

	Ground_Trans() : Transport() {	}

	Ground_Trans(int num, Ring<class Ground_Stops*> st, vector<Time> t1, vector<Time> t2, vector<Time> wt1, vector<Time> wt2, vector<int> s) : Transport(num, s)
	{
		stops = st;
		time1 = t1;
		time2 = t2;
		wtime1 = wt1;
		wtime2 = wt2;
	}

	Ground_Trans(Ground_Trans& trans)
	{
		st = trans.st;
		number = trans.number;
		stops = trans.stops;
		time1 = trans.time1;
		time2 = trans.time2;
		wtime1 = trans.wtime1;
		wtime2 = trans.wtime2;
	}

	~Ground_Trans() { }

	void setstops(Ring<class Ground_Stops*> stops);
	void settime1(vector<Time> t1);
	void settime2(vector<Time> t2);
	void setwtime1(vector<Time> t1);
	void setwtime2(vector<Time> t2);
	void pushstops(class Ground_Stops* st);
	void delstops(int type);
	void setstops(Ring<Ground_Stops>& gs, int type);

	vector<Time> fromtotime(bool a, bool b, int c);

	Ring<class Ground_Stops*> getstops();
	vector<Time> gettime1();
	vector<Time> gettime2();
	vector<Time> getwtime1();
	vector<Time> getwtime2();

	Ground_Trans& operator=(Ground_Trans& trans);
	bool operator>(Ground_Trans& T);
	bool operator<(Ground_Trans& T);

	void info();
	void stopinfo(int id);

	friend istream& operator>>(istream& stream, Ground_Trans& T);
	friend ostream& operator<<(ostream& stream, Ground_Trans& T);
	friend ifstream& operator>>(ifstream& stream, Ground_Trans& T);
	friend ofstream& operator<<(ofstream& stream, Ground_Trans& T);
};
