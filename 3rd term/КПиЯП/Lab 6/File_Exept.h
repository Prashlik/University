#pragma once
#include <fstream>
#include "Exeption.h"

class File_Exept : public Exeption
{
protected:
	int code;
public:

	File_Exept(string msg, int type) : Exeption(msg)
	{
		code = 2000 + type;
	}

	void what()
	{
		cout << "\nERROR " << code << "!  " << message << endl;
	}

	~File_Exept() {}
};

static ifstream& InFile(string adress)
{
	ifstream file;
	file.open(adress);

	try
	{
		if (!file) throw File_Exept("Cannot open the file!", UncorrectType);
	}
	catch (File_Exept& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}

static ofstream& OutFile(string adress)
{
	ofstream file;
	file.open(adress);

	try
	{
		if (!file) throw File_Exept("Cannot open the file!", UncorrectType);
	}
	catch (File_Exept& ex)
	{
		ex.what();
		exit(0);
	}

	return file;
}