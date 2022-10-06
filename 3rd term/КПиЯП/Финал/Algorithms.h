#pragma once
#include "Iterator.h"

template<class T>
class Algorithms
{
public:

	//void Sort(Iterator<T> head, Iterator<T> end, bool sort(T& obj1, T& obj2))
	//{
	//	if (head.GetCurrent() != NULL)
	//	{
	//		Iterator<T> temp;
	//		for (head; head != end; head++)
	//		{
	//			temp = head;
	//			do
	//			{
	//				if (sort(head.GetCurrent()->obj, temp.GetCurrent()->obj))
	//				{
	//					T t = head.GetCurrent()->obj;
	//					head.GetCurrent()->obj = temp.GetCurrent()->obj;
	//					temp.GetCurrent()->obj = t;
	//				}
	//				temp++;
	//			} while (temp.GetCurrent() != end.GetCurrent()->next);
	//		}
	//	}
	//	else cout << "List is empty!" << endl;
	//}

	void Find(vector<T> vect, bool comp(T& obj, string str))
	{
		if (!vect.empty())
		{
			int flg = 0;
			string data;
			cout << "Enter the data for search: ";
			cin >> data;

			for (int i = 0; i < vect.size(); i++) 
				if (comp(vect[i], data))
				{
					if (!flg)
					{
						system("cls");
						vect[0].table();
						cout << endl;
					}
					cout << vect[i] << endl;
					flg = 1;
				}

			if (flg == 0) cout << "There were no information found" << endl;
		}
		else cout << "List is empty!" << endl;
	}

	void DeleteBy(vector<T>& vect, bool comp(T& obj, string str))
	{
		if (!vect.empty())
		{
			int flg = 0;
			string data;
			cout << "Enter the data for search: "; 
			cin >> data;

			for (int i = 0;i < vect.size();i++)
			{
				if (comp(vect[i], data))
				{
					vect.erase(vect.begin() + i);
					flg = 1;
					i--;
				}
			}

			if (flg == 0)
				cout << "There were no information found" << endl;
			else cout << "Success!" << endl;
		}
		else cout << "List is empty!" << endl;

		cout << endl;
		system("pause");
	}

	void Print(vector<T>& vect)
	{
		system("cls");
		if (!vect.empty())
		{
			vect[0].table();
			cout << endl;

			for (int i = 0;i < vect.size();i++)
			{
				cout << vect[i] << endl;
			}
			cout << endl;
		}
		else cout << "List is empty!" << endl;

		cout << endl;
	}
};