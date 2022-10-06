#pragma once
#include <conio.h>

using namespace std;

class row
{
	int* line;
	int length;

public:

	row(const row& SecRow)
	{
		length = SecRow.length;

		line = new int[length];

		for (int i = 0; i < length;i++)
			line[i] = SecRow.line[i];
	};

	row(int len)
	{
		length = len;
		line = new int[length];
	};

	row()
	{
		length = 0;
		line = 0;
	};

	~row()
	{
		delete[] line;
	};

	void getrow();
	void setrow();

	row& operator=(const row&);
	row operator+(const row&);
	row operator+(int);
	row operator-(const row&);
	void operator+=(const row&);
	void operator-=(const row&);
};
