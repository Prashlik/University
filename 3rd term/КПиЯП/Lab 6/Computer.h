#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Input_Exept.h"
using namespace std;

class Computer
{
protected:

	int year;
	double price;
	string brand, name;

public:

	Computer()
	{
		year = 0;
		price = 0;
		brand = '\0';
		name = '\0';
	}

	explicit Computer(int yr, double pr, string br, string nm)
	{
		year = yr;
		price = pr;

		brand = br;
		name = nm;
	};

	~Computer() 
	{
		brand.clear();
		name.clear();
	};

	void setyear(int yr);
	void setprice(double pr);
	void setbrand(string br);
	void setname(string nm);

	int getyear();
	double getprice();
	string getbrand();
	string getname();

	void table();

	friend istream& operator>>(istream& stream, Computer& c);
	friend ostream& operator<<(ostream& stream, Computer& c);
};
