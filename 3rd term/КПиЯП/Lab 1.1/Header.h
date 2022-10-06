#pragma once
#include <vector>
#include <iostream>

using namespace std;

class row
{
	vector <int> line;

public:

	int length = 0;

	row(int len)
	{
		for (int i = 0;i < len;i++)
		{
			cin >> line[i];
		}

		length = len;
	};

//	~row()
//	{
//		delete[] line;
//	};

	void setrow();
	void getrow();

	void sum(row&);
	void sub(row&);
};
