#pragma once
#include <iostream>
#include <string> 
#include <iomanip>
#include <fstream>
#include <cstdio>
using namespace std;

class File
{
protected:
	string FileName;
	ifstream fi;
	ofstream fo;
	fstream  bfi;
	fstream  bfo;
public:
	File()
	{
		FileName = "\n";
	}
	File(string fn)
	{
		FileName = fn;
	}
	~File()
	{

	}
};