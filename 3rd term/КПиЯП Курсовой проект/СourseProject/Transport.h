#pragma once
#include "Company.h"

class Transport : public Company
{
protected:

	vector<int> st;
	int number;

public:

	Transport()
	{
		number = 0;
	}

	Transport(int num, vector<int> s)
	{
		number = num;
		st = s;
	}

	Transport(Transport& trans)
	{
		number = trans.number;
		st = trans.st;
	}

	~Transport()	{	}

	void setnumber(int num);
	void setst(vector<int> st);
	void pushst(int st);

	unsigned int getnumber();
	vector<int> getst();

	Transport& operator=(Transport& trans);

	friend istream& operator>>(istream& stream, Transport& T);
	friend ostream& operator<<(ostream& stream, Transport& T);
	friend ifstream& operator>>(ifstream& stream, Transport& T);
	friend ofstream& operator<<(ofstream& stream, Transport& T);
};
