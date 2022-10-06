#pragma once
#include "Portative.h"
#include "Input_Except.h"

class Smartphone : public Portative
{
protected:

	string type;
	int camres;

public:

	Smartphone();

	explicit Smartphone(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz, int res);

	~Smartphone() {};

	void setcamres();

	int getcamres();
	string gettype();

	void table();

	friend istream& operator>>(istream& stream, Smartphone& c);
	friend ostream& operator<<(ostream& stream, Smartphone& c);
	friend ifstream& operator>>(ifstream& stream, Smartphone& c);
	friend ofstream& operator<<(ofstream& stream, Smartphone& c);
	friend fstream& operator<<(fstream& out, Smartphone& c);
	friend fstream& operator>>(fstream& in, Smartphone& c);
};