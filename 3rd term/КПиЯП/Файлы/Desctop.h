#pragma once
#include "Computer.h"
#include "Input_Except.h"

class Desctop : public Computer
{
protected:

	string sort;
	int powersup;

public:

	Desctop();

	explicit Desctop(int yr, double pr, const char* br, const char* nm, int pow);

	~Desctop() {};

	void setpowersup();

	int getpowersup();

	void table();

	friend istream& operator>>(istream& stream, Desctop& c);
	friend ostream& operator<<(ostream& stream, Desctop& c);
	friend ifstream& operator>>(ifstream& stream, Desctop& c);
	friend ofstream& operator<<(ofstream& stream, Desctop& c);
	friend fstream& operator<<(fstream& out, Desctop& c);
	friend fstream& operator>>(fstream& in, Desctop& c);
};