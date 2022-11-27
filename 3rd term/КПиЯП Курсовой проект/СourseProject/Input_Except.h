#pragma once
#include "Exceptions.h"
#include "Structs.h"
#include "Time.h"

class Input_Except : public Exception
{
protected:
	int code;
public:

	Input_Except(string msg, int type) : Exception(msg)
	{
		code = 1000 + type;
	}

	void what()
	{
		cout << "\nERROR " << code << "!  " << message << endl;
	}

	~Input_Except() {}
};

static int InInt(int min, int max)
{
	int par;
	bool flag = false;

	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!(cin >> par) || cin.get() != '\n') throw Input_Except("Uncorrect type of input!!!", UncorrectType);

			if (par < min) throw Input_Except("Too litle number!!!", TooLittleNum);

			if (par > max) throw Input_Except("Too big number!!!", TooBigNum);

			flag = true;
		}
		catch (Input_Except& ex)
		{
			ex.what();
			cout << "It must be from " << min << " to " << max << endl;

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

	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!(cin >> par) || cin.get() != '\n') throw Input_Except("Uncorrect type of input!!!", UncorrectType);

			if (par < min) throw Input_Except("Too litle number!!!", TooLittleNum);

			if (par > max) throw Input_Except("Too big number!!!", TooBigNum);

			flag = true;
		}
		catch (Input_Except& ex)
		{
			ex.what();
			cout << "It must be from " << min << " to " << max << endl;

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return par;
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

			if (str.size() < 3) throw Input_Except("Too short string!!!\nThe length of the string should be from 2 to 10 letters.", TooShortStr);

			if (str.size() > 15) throw Input_Except("Too long string!!!\nThe length of the string should be from 2 to 10 letters.", TooLongStr);

			for (int i = 0; i < (int)str.size(); i++)
				if ((str[i] < 'A' || str[i] > 'z') && (str[i] < '0' || str[i] > '9')) throw Input_Except("Uncorrect input!!!\nThe name should contain only capital or little letters of English alphabet or digits.", NotEngLetters);

			for (int i = 0; i < (int)str.size(); i++)
				if (str[i] >= '0' && str[i] <= '9')
					j++;
			if (j == str.size()) throw Input_Except("Uncorrect input!!!\nThe name shouldn't contain only digits.", IsNotWord);

			flag = true;
		}
		catch (Input_Except& ex)
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

template <class T>
static void InName(vector<StopsInfo>& id, T& st)
{
	string name;
	int j, num, flag = false;

	for (j = 0; j < id.size();j++)
		if (id[j].id == st.getid())
			break;
	num = j;

	cout << "Enter the name of the station: \n";

	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			name = InString();
			for (j = 0; j < id.size();j++)
				if (id[j].name == name)
					if (id[j].id != st.getid())  
						throw Input_Except("This name is allready used!", AllreadyIncl);
			id[num].name = name;
			st.setname(name);

			flag = true;
		}
		catch (Input_Except& ex)
		{
			ex.what();

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);
}

static Time InTime(double max)
{
	float t;
	Time time;
	bool flag = false;

	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!(cin >> t) || cin.get() != '\n') throw Input_Except("Uncorrect type of input!!!", UncorrectType);

			if (t > max) throw Input_Except("To bid time interval!!!", TooBigInterval);

			if ((int)t > 23 || (int)t < 0) throw Input_Except("Incorrect format for entering hours!!!", UncorrectHour);

			if ((int)((t -(int)t)*100) > 59 || (int)((t - (int)t) * 100) < 0) throw Input_Except("Incorrect format for entering minutes!!!", UncorrectMin);

			time = t;

			flag = true;
		}
		catch (Input_Except& ex)
		{
			ex.what();
			cout << "Hours must be from 0 to 23, minuters must be from 0 to 59. Time interval must be less than " << max << '.' << endl;

			cout << "\nPlease try again: ";
		}
		catch (...)
		{
			cout << "\nUnknown ERROR!\nPlease try again: ";
		}

	} while (!flag);

	return time;
}