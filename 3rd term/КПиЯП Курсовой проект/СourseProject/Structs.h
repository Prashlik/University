#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
#include "Time.h"
#include "vector"
#include "Keys.h"

struct Nearest_St
{
	int id = 0;
	Time time;

	friend istream& operator>>(istream& stream, Nearest_St& S)
	{
		cout << "ID: ";
		stream >> S.id;
		cout << "Time to get to: ";
		stream >> S.time;

		return stream;
	}
	friend ostream& operator<<(ostream& stream, Nearest_St& S)
	{
		stream << setw(5) << S.id << S.time;
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Nearest_St& S)
	{
		stream >> S.id >> S.time;
		return stream;
	}
	friend ofstream& operator<<(ofstream& stream, Nearest_St& S)
	{
		stream << setw(5) << S.id;
		stream << S.time;
		return stream;
	}
};

struct StopsInfo
{
	int id = 0;
	string name = "\0";

	friend istream& operator>>(istream& stream, StopsInfo& Info)
	{
		stream >> Info.id >> Info.name;

		return stream;
	}
	friend ostream& operator<<(ostream& stream, StopsInfo& Info)
	{
		stream << setw(5) << Info.id << " " << Info.name;
		stream << endl;
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, StopsInfo& Info)
	{
		stream >> Info.id;
		stream >> Info.name;
		return stream;
	}
	friend ofstream& operator<<(ofstream& stream, StopsInfo& Info)
	{
		stream << setw(5) << Info.id;
		stream << setw(15) << Info.name;
		return stream;
	}
};