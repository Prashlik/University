#pragma once
#include <iostream>
#include <string> 
#include <iomanip>
#include <fstream>
#include "File.h"
#include "File_Except.h"
using namespace std;

template<class T>
class Binary_File : public File
{
public:
	Binary_File() {}
	Binary_File(string fn) : File(fn) {	}
	~Binary_File()
	{
		bfo.close();
		bfi.close();
	}
	fstream& getostream()
	{
		return bfo;
	}
	fstream& getistream()
	{
		return bfi;
	}
	void Open_in()
	{
		bfi = InBFile(FileName);
	}
	void Open_out()
	{
		bfo = OutBFile(FileName);
	}
	void Remote()
	{
		bfi.seekg(0, std::ios::beg);
		bfo.seekp(0, std::ios::beg);
	}
	void Read(T& obj)
	{
		bfi >> obj;
	}
	void Write(T& obj)
	{
		bfo << obj;
	}
	bool End()
	{
		if (bfi.eof()) return true;
		else return false;
	}
	bool IsEmpty()
	{
		bfi.peek();
		if (bfi.eof()) return true;
		else return false;
	}
};