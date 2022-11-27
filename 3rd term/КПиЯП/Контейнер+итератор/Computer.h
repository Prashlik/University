#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Input_Except.h"
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

	void setyear();
	void setprice();
	void setbrand();
	void setname();

	int getyear();
	double getprice();
	string getbrand();
	string getname();

	void table();

	friend istream& operator>>(istream& stream, Computer& c);
	friend ostream& operator<<(ostream& stream, Computer& c);
};

template <class T>
bool sortyear(T& obj1, T& obj2)
{
	return obj1.getyear() < obj2.getyear();
}
template <class T>
bool sortprice(T& obj1, T& obj2)
{
	return obj1.getprice() < obj2.getprice();
}
template <class T>
bool sortbrand(T& obj1, T& obj2)
{
	return obj1.getbrand() < obj2.getbrand();
}
template <class T>
bool sortname(T& obj1, T& obj2)
{
	return obj1.getname() < obj2.getname();
}
