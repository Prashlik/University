#include <iostream>
#include <conio.h>
#include <string>
#pragma once

using namespace std;

enum errors
{
	UncorrectType = 1,
	NegativeNum,
	TooLittleNum,
	TooBigNum,
	NotEngLetters,
	TooShortStr,
	TooLongStr,
	IsNotWord,
	NotBigLetter
};

class Exception
{
protected:
	string message;
public:

	Exception(string msg) : message(msg){ }

	void what()
	{
		cout << "\nERROR! " << message << endl;
	}

	~Exception() {}
};