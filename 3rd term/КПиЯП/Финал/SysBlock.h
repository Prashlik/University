#pragma once
#include "Desctop.h"
#include "Input_Except.h"

class SysBlock : public Desctop
{
protected:

	string type, motherboard;
	double high, weight;

public:

	SysBlock();

	explicit SysBlock(int yr, double pr, const char* br, const char* nm, int pow, double hig, double wgh, string mtr);

	~SysBlock() 
	{
		motherboard.clear();
	};

	void setmotherboard();
	void sethigh();
	void setweight();

	string getmotherboard();
	double gethigh();
	double getweight();
	string gettype();

	void table();

	friend istream& operator>>(istream& stream, SysBlock& c);
	friend ostream& operator<<(ostream& stream, SysBlock& c);
	friend ifstream& operator>>(ifstream& stream, SysBlock& c);
	friend ofstream& operator<<(ofstream& stream, SysBlock& c);
	friend fstream& operator<<(fstream& out, SysBlock& c);
	friend fstream& operator>>(fstream& in, SysBlock& c);
};