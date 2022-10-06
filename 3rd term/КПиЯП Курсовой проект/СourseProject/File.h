#pragma once
#include <iostream>
#include <string> 
#include <iomanip>
#include <fstream>
#include<cstdio>
using namespace std;

class File 
{
protected:
	string fname;
	ifstream fin;
	ofstream fout;
public:
	File() 
	{
		fname = "\n";
	}
	File(string fn)
	{
		fname = fn;
	}
	~File()
	{
	
	}
};