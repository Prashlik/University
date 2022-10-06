#pragma once
#include <vector>
#include <algorithm>
#include "Header.h"
#include "Template.h"
#include "Algorithms.h"
#include "Text_File.h"
#include "Binary_File.h"
#include "Keys.h"


template <class T>
class Interface
{
	T obj;

public:

	Interface() {}
	~Interface() {}

	void Choose()
	{
		bool flag = 0;
		char f;

		do
		{

			system("cls");
			rewind(stdin);

			cout << "0. Exit the program" << endl;
			cout << "1. Create a vector of the smartphones" << endl;
			cout << "2. Create a vector of the laptops" << endl;
			cout << "3. Create a vector of the system blocks" << endl;
			cout << "4. Create a vector of the monoblocks" << endl;

			switch (f = _getch())
			{
			case '1':
			{
				Interface<Smartphone> sm;
				sm.Menu();
				flag = 1;
				break;
			}
			case '2':
			{
				Interface<Laptop> lt;
				lt.Menu();
				flag = 1;
				break;
			}
			case '3':
			{
				Interface<SysBlock> sb;
				sb.Menu();
				flag = 1;
				break;
			}
			case '4':
			{
				Interface<Monoblock> mb;
				mb.Menu();
				flag = 1;
				break;
			}
			}

		} while (f != '0');
	}

	void Menu()
	{
		Algorithms<T> alg;
		vector<T> comps;
		bool flag = 0, key = 0;
		int vflag = 1;
		do {
			do {
				flag = 0;
				rewind(stdin);
				system("cls");
				cout << "================= MENU ==================" << endl;
				cout << "||===== [Esc] - Exit the program ======||" << endl;
				if (vflag == 1)
					cout << "||--------[1.Show your vector]---------||" << endl;
				else
					cout << "||-------- 1.Show your vector ---------||" << endl;
				if (vflag == 2)
					cout << "||--------[2.Add a new element]--------||" << endl;
				else
					cout << "||-------- 2.Add a new element --------||" << endl;
				if (vflag == 3)
					cout << "||---[3.Delete an element by number]---||" << endl;
				else
					cout << "||--- 3.Delete an element by number ---||" << endl;
				if (vflag == 4)
					cout << "||--[4.Delete the element(s) by data]--||" << endl;
				else
					cout << "||-- 4.Delete the element(s) by data --||" << endl;
				if (vflag == 5)
					cout << "||--------[5.Delete the vector]--------||" << endl;
				else 
					cout << "||-------- 5.Delete the vector --------||" << endl;
				if (vflag == 6)
					cout << "||---------[6.Sort the vector]---------||" << endl;
				else 
					cout << "||--------- 6.Sort the vector ---------||" << endl;
				if (vflag == 7)
					cout << "||------[7.Find the element(s)]--------||" << endl;
				else
					cout << "||------ 7.Find the element(s) --------||" << endl;
				if (vflag == 8)
					cout << "||------------[8.Text file]------------||" << endl;
				else 
					cout << "||------------ 8.Text file ------------||" << endl;
				cout << "||=====================================||" << endl;

				do {
					key = 0;
					if (_kbhit())
					{
						switch (static_cast<Keys>(_getch()))
						{
						case Keys::UP:
							if (vflag == 1)
								vflag = 8;
							else vflag--;
							key++;
							break;
						case Keys::DOWN:
							if (vflag == 8)
								vflag = 1;
							else vflag++;
							key++;
							break;
						case Keys::ESC:
							vflag = 0;
							flag++;
							key++;
							break;
						case Keys::ENTER:
							flag++;
							key++;
							break;
						}
					}
				} while (!key);
			} while (!flag);

			switch (vflag)
			{
			case 1:
			{
				alg.Print(comps);
				system("pause");
				break;
			}
			case 2:
			{
				T value;
				cin >> value;
				comps.push_back(value);
				break;
			}
			case 3:
			{
				alg.Print(comps);
				if (!comps.empty())
				{
					int n;
					cout << "\n\nEnter the number of the element: ";
					n = InInt(1, comps.size());
					comps.erase(comps.begin() + n - 1);
					alg.Print(comps);
					system("pause");
				}
				else system("pause");
				break;
			}
			case 4:
			{
				deleteby(comps);
				break;
			}
			case 5:
			{
				comps.clear();
				cout << "\nSuccess!\n";
				system("pause");
				break;
			}
			case 6:
			{
				fsort(comps);
				break;
			}
			case 7:
			{
				find(comps);
				break;
			}
			case 8:
			{
				file(comps);
				break;
			}
			}
		} while (vflag);
	}
	
	void file(vector<T>& comps)
	{
		bool flag = 0, key = 0;
		int vflag = 1, hflag = 1;
		do {
			do {
				flag = 0;
				rewind(stdin);
				system("cls");
				cout << "================= FILE ==================" << endl;
				cout << "||========= [Esc] - turn back =========||" << endl;
				if (hflag == 1)
					cout << "||-------[TEXT]--------- BINARY -------||" << endl;
				else
					cout << "||------- TEXT ---------[BINARY]-------||" << endl;
				if (vflag == 1)
					cout << "||--------------[1.Read]---------------||" << endl;
				else
					cout << "||-------------- 1.Read ---------------||" << endl;
				if (vflag == 2)
					cout << "||--------------[2.Write]--------------||" << endl;
				else
					cout << "||-------------- 2.Write --------------||" << endl;
				cout << "||=====================================||" << endl;

				do {
					key = 0;
					if (_kbhit())
					{
						switch (static_cast<Keys>(_getch()))
						{
						case Keys::UP:
							if (vflag == 1)
								vflag = 2;
							else vflag--;
							key++;
							break;
						case Keys::DOWN:
							if (vflag == 2)
								vflag = 1;
							else vflag++;
							key++;
							break;
						case Keys::LEFT:
							if (hflag == 1)
								hflag = 2;
							else hflag--;
							key++;
							break;
						case Keys::RIGHT:
							if (hflag == 2)
								hflag = 1;
							else hflag++;
							key++;
							break;
						case Keys::ESC:
							vflag = 0;
							flag++;
							key++;
							break;
						case Keys::ENTER:
							flag++;
							key++;
							break;
						}
					}
				} while (!key);
			} while (!flag);
			
			switch (vflag)
			{
			case 1:
			{
				if (hflag == 1)
				{
					comps.clear();
					T temp;
					Text_File<T> file("Data\\" + temp.gettype() + ".txt");
					file.Open_in();
					while (!file.End())
					{
						file.Read(temp);
						comps.push_back(temp);
					}
					cout << "Success!" << endl;
					system("pause");
				}
				else
				{
					comps.clear();
					int numb;
					T temp;
					Binary_File<T> file("BData\\" + temp.gettype() + ".dat");
					file.Open_in();
					fstream& st = file.getistream();
					st.read(reinterpret_cast<char*>(&numb), sizeof(int));
					for (int i = 0; i < numb; i++)
					{
						file.Read(temp);
						comps.push_back(temp);
					}
					cout << "Success!" << endl;
					system("pause");
				}
				flag++;
				break;
			}
			case 2:
			{
				if (hflag == 1)
				{
					T temp;
					if (comps.empty())
					{
						cout << "The list is empty!\n\n";
						system("pause");
						return;
					}
					Text_File<T> file("Data\\" + temp.gettype() + ".txt");
					file.Open_out();
					for (int i = 0; i < comps.size(); i++)
						file.Write(comps[i]);
					cout << "Success!" << endl;
					system("pause");
				}
				else 
				{
					T temp;
					if (comps.empty())
					{
						cout << "The list is empty!\n\n";
						system("pause");
						return;
					}
					Binary_File<T> file("BData\\" + temp.gettype() + ".dat");
					file.Open_out();
					fstream& st = file.getostream();
					st.write(reinterpret_cast<char*>(comps.size()), sizeof(int));
					for (int i = 0; i < comps.size(); i++)
						file.Write(comps[i]);
					cout << "Success!" << endl;
					system("pause");
				}
				flag++;
				break;
			}
			}
		} while (!flag);
	}

	void fsort(vector<T>& comps)
	{
		if (comps.empty())
		{
			cout << "The list is empty!\n\n";
			system("pause");
			return;
		}

		Algorithms<T> alg;
		bool flag = 0, key = 0;
		int vflag = 1;
		do {
			do {
				flag = 0;
				rewind(stdin);
				system("cls");
				cout << "================= SORT ==================" << endl;
				cout << "||========= [Esc] - turn back =========||" << endl;
				if (vflag == 1)
					cout << "||----------[1.Sort by year]-----------||" << endl;
				else
					cout << "||---------- 1.Sort by year -----------||" << endl;
				if (vflag == 2)
					cout << "||----------[2.Sort by price]----------||" << endl;
				else
					cout << "||---------- 2.Sort by price ----------||" << endl;
				if (vflag == 3)
					cout << "||----------[3.Sort by name]-----------||" << endl;
				else
					cout << "||---------- 3.Sort by name -----------||" << endl;
				if (vflag == 4)
					cout << "||----------[4.Sort by brand]----------||" << endl;
				else
					cout << "||---------- 4.Sort by brand ----------||" << endl;
				cout << "||=====================================||" << endl;

				do {
					key = 0;
					if (_kbhit())
					{
						switch (static_cast<Keys>(_getch()))
						{
						case Keys::UP:
							if (vflag == 1)
								vflag = 4;
							else vflag--;
							key++;
							break;
						case Keys::DOWN:
							if (vflag == 4)
								vflag = 1;
							else vflag++;
							key++;
							break;
						case Keys::ESC:
							vflag = 0;
							flag++;
							key++;
							break;
						case Keys::ENTER:
							flag++;
							key++;
							break;
						}
					}
				} while (!key);
			} while (!flag);

			switch (vflag)
			{
			case 1:
				sort(comps.begin(), comps.end(), [](T& a, T& b) {return (a.getyear() < b.getyear()); });
				cout << endl;
				alg.Print(comps);
				system("pause");
				break;
			case 2:
				sort(comps.begin(), comps.end(), [](T& a, T& b) {return (a.getprice() < b.getprice()); });
				cout << endl;
				alg.Print(comps);
				system("pause");
				break;
			case 3:
				sort(comps.begin(), comps.end(), [](T& a, T& b) {return (a.getname() < b.getname()); });
				cout << endl;
				alg.Print(comps);
				system("pause");
				break;
			case 4:
				sort(comps.begin(), comps.end(), [](T& a, T& b) {return (a.getbrand() < b.getbrand()); });
				cout << endl;
				alg.Print(comps);
				system("pause");
				break;
			}
		} while (vflag);
	};

	void find(vector<T>& comps)
	{
		if (comps.empty())
		{
			cout << "The list is empty!\n\n";
			system("pause");
			return;
		}

		Algorithms<T> alg;
		bool flag = 0, key = 0;
		int vflag = 1;
		do {
			do {
				flag = 0;
				rewind(stdin);
				system("cls");
				cout << "================= FIND ==================" << endl;
				cout << "||========= [Esc] - turn back =========||" << endl;
				if (vflag == 1)
					cout << "||----------[1.Find by year]-----------||" << endl;
				else
					cout << "||---------- 1.Find by year -----------||" << endl;
				if (vflag == 2)
					cout << "||----------[2.Find by price]----------||" << endl;
				else
					cout << "||---------- 2.Find by price ----------||" << endl;
				if (vflag == 3)
					cout << "||----------[3.Find by name]-----------||" << endl;
				else
					cout << "||---------- 3.Find by name -----------||" << endl;
				if (vflag == 4)
					cout << "||----------[4.Find by brand]----------||" << endl;
				else
					cout << "||---------- 4.Find by brand ----------||" << endl;
				cout << "||=====================================||" << endl;

				do {
					key = 0;
					if (_kbhit())
					{
						switch (static_cast<Keys>(_getch()))
						{
						case Keys::UP:
							if (vflag == 1)
								vflag = 4;
							else vflag--;
							key++;
							break;
						case Keys::DOWN:
							if (vflag == 4)
								vflag = 1;
							else vflag++;
							key++;
							break;
						case Keys::ESC:
							vflag = 0;
							flag++;
							key++;
							break;
						case Keys::ENTER:
							flag++;
							key++;
							break;
						}
					}
				} while (!key);
			} while (!flag);

			switch (vflag)
			{
			case 1:
				alg.Find(comps, compyear);
				cout << endl;
				system("pause");
				break;
			case 2:
				alg.Find(comps, compprice);
				cout << endl;
				system("pause");
				break;
			case 3:
				alg.Find(comps, compname);
				cout << endl;
				system("pause");
				break;
			case 4:
				alg.Find(comps, compbrand);
				cout << endl;
				system("pause");
				break;
			}
		} while (!flag);
	};

	void deleteby(vector<T>& comps)
	{
		if (comps.empty())
		{
			cout << "The list is empty!\n\n";
			system("pause");
			return;
		}

		Algorithms<T> alg;
		bool flag = 0, key = 0;
		int vflag = 1;
		do {
			do {
				flag = 0;
				rewind(stdin);
				system("cls");
				cout << "================= FIND ==================" << endl;
				cout << "||========= [Esc] - turn back =========||" << endl;
				if (vflag == 1)
					cout << "||---------[1.Delete by year]----------||" << endl;
				else
					cout << "||--------- 1.Delete by year ----------||" << endl;
				if (vflag == 2)
					cout << "||---------[2.Delete by price]---------||" << endl;
				else
					cout << "||--------- 2.Delete by price ---------||" << endl;
				if (vflag == 3)
					cout << "||---------[3.Delete by name]----------||" << endl;
				else
					cout << "||--------- 3.Delete by name ----------||" << endl;
				if (vflag == 4)
					cout << "||---------[4.Delete by brand]---------||" << endl;
				else
					cout << "||--------- 4.Delete by brand ---------||" << endl;
				cout << "||=====================================||" << endl;

				do {
					key = 0;
					if (_kbhit())
					{
						switch (static_cast<Keys>(_getch()))
						{
						case Keys::UP:
							if (vflag == 1)
								vflag = 4;
							else vflag--;
							key++;
							break;
						case Keys::DOWN:
							if (vflag == 4)
								vflag = 1;
							else vflag++;
							key++;
							break;
						case Keys::ESC:
							vflag = 0;
							flag++;
							key++;
							break;
						case Keys::ENTER:
							flag++;
							key++;
							break;
						}
					}
				} while (!key);
			} while (!flag);

			switch (vflag)
			{
			case 1:
				alg.DeleteBy(comps, compyear);
				break;
			case 2:
				alg.DeleteBy(comps, compprice);
				break;
			case 3:
				alg.DeleteBy(comps, compname);
				break;
			case 4:
				alg.DeleteBy(comps, compbrand);
				break;
			}
		} while (!flag);
	};

};
