#pragma once
#include <fstream>
#include "Exceptions.h"

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
	file.open(adress, ios::in);

	try
	{
		if (!file.is_open()) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(-1);
	}

	return file;
}

static ofstream OutFile(string adress)
{
	ofstream file;
	file.open(adress, ios::out);

	try
	{
		if (!file.is_open()) throw File_Except("Cannot open the file!", UncorrectType);
	}
	catch (File_Except& ex)
	{
		ex.what();
		exit(-1);
	}

	return file;
}