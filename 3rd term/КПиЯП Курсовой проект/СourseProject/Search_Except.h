#pragma once
#include "Exceptions.h"
#include "Ground_Trans.h"
#include "Template.h"

class Search_Except : public Exception
{
protected:
	int code;
public:

	Search_Except(string msg, int type) : Exception(msg)
	{
		code = 3000 + type;
	}

	void what()
	{
		cout << "\nERROR " << code << "!  " << message << endl;
	}

	~Search_Except() {}
};

static int SearchGTrans(Ring<Ground_Trans>& trans)
{
	int numb, i, f = 0;
	bool flag = false;

	do
	{
		rewind(stdin);
		cin.clear();
		 
		try
		{
			if (!trans.getsize())
			{
				cout << "There are no route with this type of transport!" << endl;
				system("pause");
				return - 1;
			}

			cout << "Enter the number of the route: ";
				numb = InInt(1, trans[trans.getsize() - 1].getnumber());
				for (i = 0; i < trans.getsize();i++)
					if (trans[i].getnumber() == numb)
					{
						f = 1;
						break;
					}
				if (f != 1) throw Input_Except("There is no route with this number!!!", IsNotExist);

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

	return i;
}

template <class T>
static int SearchStop(T& st)
{
	int i, f = 0;
	bool flag = false;
	string name;

	do
	{
		rewind(stdin);
		cin.clear();

		try
		{
			if (!st.getsize())
			{
				cout << "There are no stops!" << endl;
				system("pause");
				return -1;
			}
			cout << "Enter the name of the station: \n";
			name = InString();
			for (i = 0; i < st.getsize();i++)
				if (st[i].getname() == name)
				{
					f = 1;
					break;
				}
			if (f != 1) throw Input_Except("There is no route with this number!!!", IsNotExist);

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

	return i;
}