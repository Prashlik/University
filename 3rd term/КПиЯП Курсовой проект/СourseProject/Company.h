#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
#include "Time.h"
#include "vector"
#include "Input_Except.h"
#include "Keys.h"

using namespace std;

class Company
{
private:

	string CompanyName;

public:

	Company()
	{
		CompanyName = "MyTrans";
	}

	Company(string name)
	{
		CompanyName = name;
	}

	void setcname(string nm)
	{
		CompanyName = nm;
	}

	string getcname()
	{
		return CompanyName;
	}
};
