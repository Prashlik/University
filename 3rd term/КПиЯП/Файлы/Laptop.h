#pragma once
#include "Portative.h"
#include "Input_Except.h"

class Laptop : public Portative
{
protected:

	string type;
	int usb;

public:

	Laptop();

	explicit Laptop(int yr, double pr, const char* br, const char* nm, int bat, int tm, double sz, int nusb);

	~Laptop() {};

	void setusb();

	int getusb();
	string gettype();

	void table();

	friend istream& operator>>(istream& stream, Laptop& c);
	friend ostream& operator<<(ostream& stream, Laptop& c);
	friend ifstream& operator>>(ifstream& stream, Laptop& c);
	friend ofstream& operator<<(ofstream& stream, Laptop& c);
	friend fstream& operator<<(fstream& out, Laptop& c);
	friend fstream& operator>>(fstream& in, Laptop& c);
};