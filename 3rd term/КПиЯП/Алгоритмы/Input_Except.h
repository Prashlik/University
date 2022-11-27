#pragma once
#include "Exception.h"

class Input_Exept : public Exception
{
protected:
	int code;
public:

	Input_Exept(string msg, int type) : Exception(msg)
	{
		code = 1000 + type;
	}

	void what()
	{
		cout << "\nERROR " << code << "!  " << message << endl;
	}

	~Input_Exept() {}
};

static int InInt(int min, int max)
{
	int par;
	bool flag = false;

	cout << "\n(The number must be more than " << min << " and less than " << max << ")" << endl;
	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!(cin >> par) || cin.get() != '\n') throw Input_Exept("Uncorrect type of input!!!", UncorrectType);

			if (par < min) throw Input_Exept("Too litle number!!!", TooLittleNum);

			if (par > max) throw Input_Exept("Too big number!!!", TooBigNum);

			flag = true;
		}
		catch (Input_Exept& ex)
		{
			ex.what();
			cout << "It must be more than " << min << " and less then " << max << endl;

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return par;
}

static double InDouble(double min, double max)
{
	double par;
	bool flag = false;

	cout << "\n(The number must be more than " << min << " and less than " << max << ")" << endl;
	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!(cin >> par) || cin.get() != '\n') throw Input_Exept("Uncorrect type of input!!!", UncorrectType);

			if (par < min) throw Input_Exept("Too litle number!!!", TooLittleNum);

			if (par > max) throw Input_Exept("Too big number!!!", TooBigNum);

			flag = true;
		}
		catch (Input_Exept& ex)
		{
			ex.what();
			cout << "It must be more than " << min << "and less then " << max << endl;

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return par;
}

static string InName()
{
	string name;
	bool flag = false;
	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			cin >> name;

			if (name.size() < 2) throw Input_Exept("Too short string!!!\nThe length of the string should be from 2 to 10 letters.", TooShortStr);

			if (name.size() > 10) throw Input_Exept("Too long string!!!\nThe length of the string should be from 2 to 10 letters.", TooLongStr);

			if (name[0] < 'A' || name[0] > 'Z') throw Input_Exept("It isn`t name!!!\nThe first letter should be the capital letter.", NotBigLetter);

			for (int i = 0; i < (int)name.size(); i++)
				if (name[i] < 'A' || name[i] > 'z') throw Input_Exept("It isn`t a name!!!\nThe name should contain only capital or little letters of English alphabet.", NotEngLetters);

			flag = true;
		}
		catch (Input_Exept& ex)
		{
			ex.what();

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return name;
}

static string InString()
{
	string str;
	int j;
	bool flag = false;
	do
	{
		rewind(stdin);
		cin.clear();
		j = 0;

		try
		{
			cin >> str;

			if (str.size() < 2) throw Input_Exept("Too short string!!!\nThe length of the string should be from 2 to 10 letters.", TooShortStr);

			if (str.size() > 10) throw Input_Exept("Too long string!!!\nThe length of the string should be from 2 to 10 letters.", TooLongStr);

			for (int i = 0; i < (int)str.size(); i++)
				if ((str[i] < 'A' || str[i] > 'z') && (str[i] < '0' || str[i] > '9')) throw Input_Exept("Uncorrect input!!!\nThe name should contain only capital or little letters of English alphabet or digits.", NotEngLetters);

			for (int i = 0; i < (int)str.size(); i++)
				if (str[i] >= '0' && str[i] <= '9')
					j++;
			if (j == str.size()) throw Input_Exept("Uncorrect input!!!\nThe name shouldn't contain only digits.", IsNotWord);

			flag = true;
		}
		catch (Input_Exept& ex)
		{
			ex.what();

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return str;
}