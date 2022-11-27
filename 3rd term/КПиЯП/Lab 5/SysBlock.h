#pragma once
#include "Desctop.h"

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

	void setmotherboard(string mtr);
	void sethigh(float hig);
	void setweight(float wgh);

	string getmotherboard();
	double gethigh();
	double getweight();

	void table();

	friend istream& operator>>(istream& stream, SysBlock& c);
	friend ostream& operator<<(ostream& stream, SysBlock& c);
};