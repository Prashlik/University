#pragma once
#include "Desctop.h"
#include "Input_Except.h"

class Monoblock : public Desctop
{
protected:

	string type;
	double screen;

public:

	Monoblock();

	explicit Monoblock(int yr, double pr, const char* br, const char* nm, int pow, double scr, double wgh, string mtr);

	~Monoblock() {};

	void setscreen();

	double getscreen();
	string gettype();

	void table();

	friend istream& operator>>(istream& stream, Monoblock& c);
	friend ostream& operator<<(ostream& stream, Monoblock& c);
	friend ifstream& operator>>(ifstream& stream, Monoblock& c);
	friend ofstream& operator<<(ofstream& stream, Monoblock& c);
	friend fstream& operator<<(fstream& out, Monoblock& c);
	friend fstream& operator>>(fstream& in, Monoblock& c);
};