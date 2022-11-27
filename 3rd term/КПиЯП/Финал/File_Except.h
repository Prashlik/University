#pragma once
#include <fstream>
#include "Exception.h"

class File_Except : public Exception
{
protected:
	int code;
public:

	File_Except(string msg, int type) : Exception(msg)
	{
		code = 2000 + type;
	}

	void what()
	{
		cout << "\nERROR " << code << "!  " << message << endl;
	}

	~File_Except() {}
};

static ifstream InFile(string adress)
{
	ifstream file;
	file.open(adress);

	try
	{
		if (!file) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}

static ofstream OutFile(string adress)
{
	ofstream file;
	file.open(adress);

	try
	{
		if (!file) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}

static fstream InBFile(string adress)
{
	fstream file;
	file.open(adress, ios::in | ios::binary);

	try
	{
		if (!file) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}

static fstream OutBFile(string adress)
{
	fstream file;
	file.open(adress, ios::out | ios::binary);

	try
	{
		if (!file) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}