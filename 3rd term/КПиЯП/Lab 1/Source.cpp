#include <iostream>
#include "header.h"

using namespace std;

void row::getrow()
{
	for (int i = 0;i < length;i++)
	{
		cout << i << ": " << line[i] << "	";
	}

	cout << endl;
};

void row::setrow()
{
	for (int i = 0; i < length; i++)
		cin >> line[i];
}

row& row::operator=(const row& SecRow)
{
	length = SecRow.length;

	delete[] line;

	line = new int[length];

	for (int i = 0; i < length;i++)
		line[i] = SecRow.line[i];

	return *this;
}

row row::sum(const row& SecRow)
{
	row NewRow;
	int i = 0;

	if (length > SecRow.length)
	{
		NewRow.length = length;
		NewRow.line = new int[NewRow.length];

		for (i; i < SecRow.length;i++)
			NewRow.line[i] = line[i] + SecRow.line[i];

		for (i; i < NewRow.length; i++)
			NewRow.line[i] = line[i];
	}
	else
	{
		NewRow.length = SecRow.length;
		NewRow.line = new int[NewRow.length];

		for (i; i < length;i++)
			NewRow.line[i] = line[i] + SecRow.line[i];

		for (i; i < NewRow.length; i++)
			NewRow.line[i] = SecRow.line[i];
	}

	return NewRow;
};

row row::sub(const row& SecRow)
{
	row NewRow;
	int i = 0;

	if (length > SecRow.length)
	{
		NewRow.length = length;
		NewRow.line = new int[NewRow.length];

		for (i; i < SecRow.length;i++)
			NewRow.line[i] = line[i] - SecRow.line[i];

		for (i; i < NewRow.length; i++)
			NewRow.line[i] = line[i];
	}
	else
	{
		NewRow.length = SecRow.length;
		NewRow.line = new int[NewRow.length];

		for (i; i < length;i++)
			NewRow.line[i] = line[i] - SecRow.line[i];

		for (i; i < NewRow.length; i++)
			NewRow.line[i] = 0 - SecRow.line[i];
	}

	return NewRow;
};