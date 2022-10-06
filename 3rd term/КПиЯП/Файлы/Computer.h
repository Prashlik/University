#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <conio.h>
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
	friend ifstream& operator>>(ifstream& stream, Computer& c);
	friend ofstream& operator<<(ofstream& stream, Computer& c);
	friend fstream& operator<<(fstream& out, Computer& c);
	friend fstream& operator>>(fstream& in, Computer& c);
};

template <class T>
bool sortyear(T& obj1, T& obj2)
{
	return obj1.getyear() > obj2.getyear();
}
template <class T>
bool sortprice(T& obj1, T& obj2)
{
	return obj1.getprice() > obj2.getprice();
}
template <class T>
bool sortbrand(T& obj1, T& obj2)
{
	return obj1.getbrand() > obj2.getbrand();
}
template <class T>
bool sortname(T& obj1, T& obj2)
{
	return obj1.getname() > obj2.getname();
}

template <class T>
bool compyear(T& obj, string str)
{
	return to_string(obj.getyear()) == str;
}
template <class T>
bool compprice(T& obj, string str)
{
	int i, f = 0;
	string price = to_string(obj.getprice());
	for (i = 0; str[i] != '\0' && price[i] != '\0'; i++)
	{
		if (str[i] != price[i])
			return 0;
		if (str[i] == '.') f = 1;
	}
	if ((str[i] == '\0') & (price[i] == '.' && price[i + 1] == '0'))
		return 1;
	if (f)
		if ((str[i] == '\0') & (price[i] == '0'))
			return 1;
	if ((str[i] != '\0') & (price[i] != '\0'))
		return 1;
	return 0;
}
template <class T>
bool compbrand(T& obj, string str)
{
	return obj.getbrand() == str;
}
template <class T>
bool compname(T& obj, string str)
{
	return obj.getname() == str;
}
