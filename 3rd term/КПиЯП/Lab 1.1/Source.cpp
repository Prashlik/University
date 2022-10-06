#include <iostream>
#include "header.h"

using namespace std;

void row::setrow()
{
	for (int i = 0;i < length;i++)
	{
		cout << endl << i << ": ";
		cin >> line[i];
	}
};

void row::getrow()
{
	for (int i = 0;i < length;i++)
	{
		cout << i << ": " << line[i] << "  ";
	}

	cout << endl;
};

void row::sum(row &SecRow)
{
	if (length < SecRow.length)
	{
		for (int i = length; i < SecRow.length;i++)
		{
			line[i] = 0;
		}
		
	}

	getrow();
	cout << "+\n";
	SecRow.getrow();
	cout << "=\n";

	for (int i = 0;i < SecRow.length;i++)
	{
		row::line[i] += SecRow.line[i];
	}
};

void row::sub(row& SecRow)
{
	if (length < SecRow.length)
	{
		for (int i = length; i < SecRow.length;i++)
		{
			line[i] = 0;
		}

	}

	getrow();
	cout << "-\n";
	SecRow.getrow();
	cout << "=\n";

	for (int i = 0;i < SecRow.length;i++)
	{
		row::line[i] -= SecRow.line[i];
	}
};


