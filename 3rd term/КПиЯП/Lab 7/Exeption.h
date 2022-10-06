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

class Exeption
{
protected:
	string message;
public:

	Exeption(string msg) : message(msg){ }

	void what()
	{
		cout << "\nERROR! " << message << endl;
	}

	~Exeption() {}
};