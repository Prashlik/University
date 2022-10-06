#pragma once
#include "Desctop.h"
#include "Input_Exept.h"

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

	void table();

	friend istream& operator>>(istream& stream, Monoblock& c);
	friend ostream& operator<<(ostream& stream, Monoblock& c);
};