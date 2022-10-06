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
		fo.close();
		fi.close();
	}
	void Open_in()
	{
		fi = InFile(FileName);
	}
	void Open_out()
	{
		fo = OutFile(FileName);
	}
	void Read(T& obj)
	{
		fi >> obj;
	}
	void Remote()
	{
		fi.seekg(0, std::ios::beg);
		fo.seekp(0, std::ios::beg);
	}
	void Write(T& obj)
	{
		fo << endl;
		fo << obj;
	}
	bool End()
	{
		if (fi.eof()) return true;
		else return false;
	}
	bool IsEmpty()
	{
		fi.peek();
		if (fi.eof()) return true;
		else return false;
	}
};