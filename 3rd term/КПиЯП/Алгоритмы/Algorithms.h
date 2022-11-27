#pragma once
#include "Iterator.h"

template<class T>
class Algorithms
{
public:

	void Sort(Iterator<T> head, Iterator<T> end, bool sort(T& obj1, T& obj2))
	{
		if (head.GetCurrent() != NULL)
		{
			Iterator<T> temp;
			for (head; head != end; head++)
			{
				temp = head;
				do
				{
					if (sort(head.GetCurrent()->obj, temp.GetCurrent()->obj))
					{
						T t = head.GetCurrent()->obj;
						head.GetCurrent()->obj = temp.GetCurrent()->obj;
						temp.GetCurrent()->obj = t;
					}
					temp++;
				} while (temp.GetCurrent() != end.GetCurrent()->next);
			}
		}
		else cout << "List is empty!" << endl;
	}

	void Find(Iterator<T> begin, Iterator<T> end, bool comp(T& obj, string str))
	{
		if (begin.GetCurrent() != NULL)
		{
			int flg = 0;
			string data;
			Iterator<T> temp = begin;
			cout << "Enter the data for search: ";
			cin >> data;

			do {
				if (comp(temp.GetCurrent()->obj, data))
				{
					if (!flg)
					{
						system("cls");
						(*temp).table();
						cout << endl;
					}
					cout << *temp << endl;
					flg = 1;
				}
				temp ++;
			} while (temp.GetCurrent() != end.GetCurrent()->next);

			if (flg == 0) cout << "There were no information found" << endl;
		}
		else cout << "List is empty!" << endl;
	}

	void DeleteBy(Ring<T>& ring, bool comp(T& obj, string str))
	{
		if (ring.IsNotEmpty())
		{
			int flg = 0;
			string data;
			cout << "Enter the data for search: "; 
			cin >> data;

			for (int i = 0;i < ring.getsize();i++)
			{
				if (comp(ring[i], data))
				{
					ring.DeleteOneNode(i);
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
};