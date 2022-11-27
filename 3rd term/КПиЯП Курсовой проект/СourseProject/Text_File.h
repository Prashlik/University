#pragma once
#include <iostream>
#include <string> 
#include <iomanip>
#include <fstream>
#include "File.h"
#include "File_Except.h"
using namespace std;

template<class T>
class Text_File : public File
{
public:
	Text_File() {}
	Text_File(string fn) : File(fn) {	}
	~Text_File()
	{
		fout.close();
		fin.close();
	}
	void Open_in()
	{
		fin = InFile(fname);
	}
	void Open_out()
	{
		fout = OutFile(fname);
	}
	void Read(T& obj)
	{
		fin >> obj;
	}
	void Remote()
	{
		fin.seekg(0, std::ios::beg);
		fout.seekp(0, std::ios::beg);
	}
	void Write(T& obj)
	{
		fout << endl;
		fout << obj;
	}
	bool End()
	{
		if (fin.eof()) return true;
		else return false;
	}
	bool IsEmpty()
	{
		fin.peek();
		if (fin.eof()) return true;
		else return false;
	}
};