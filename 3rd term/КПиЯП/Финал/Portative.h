#pragma once
#include "Computer.h"
#include "Input_Except.h"

class Portative : public Computer
{
protected:

	string sort = "\0";
	int battery = 0, time = 0;
	double screen = 0;

public:

	Portative();

	explicit Portative(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz);

	~Portative() {};

	void setbattery();
	void settime();
	void setscreen();

	int getbattery();
	int gettime();
	double getscreen();

	void table();

	friend istream& operator>>(istream& stream, Portative& c);
	friend ostream& operator<<(ostream& stream, Portative& c);
	friend ifstream& operator>>(ifstream& stream, Portative& c);
	friend ofstream& operator<<(ofstream& stream, Portative& c);
	friend fstream& operator<<(fstream& out, Portative& c);
	friend fstream& operator>>(fstream& in, Portative& c);
};