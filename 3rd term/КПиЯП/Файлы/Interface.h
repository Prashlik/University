#pragma once
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
			cout << "1. Create a ring of the smartphones" << endl;
			cout << "2. Create a ring of the laptops" << endl;
			cout << "3. Create a ring of the system blocks" << endl;
			cout << "4. Create a ring of the monoblocks" << endl;

			switch (f = _getch())
			{
			case '1':
			{
				Interface<Smartphone> RingSmartphone;
				RingSmartphone.Menu();
				flag = 1;
				break;
			}
			case '2':
			{
				Interface<Laptop> RingLaptop;
				RingLaptop.Menu();
				flag = 1;
				break;
			}
			case '3':
			{
				Interface<SysBlock> RingSysBlock;
				RingSysBlock.Menu();
				flag = 1;
				break;
			}
			case '4':
			{
				Interface<Monoblock> RingMonoblock;
				RingMonoblock.Menu();
				flag = 1;
				break;
			}
			}

		} while (f != '0');
	}

	void Menu()
	{
		Ring<T> ring;
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
					cout << "||---------[1.Show your ring]----------||" << endl;
				else
					cout << "||--------- 1.Show your ring ----------||" << endl;
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
					cout << "||---------[5.Delete the ring]---------||" << endl;
				else 
					cout << "||--------- 5.Delete the ring ---------||" << endl;
				if (vflag == 6)
					cout << "||----------[6.Sort the ring]----------||" << endl;
				else 
					cout << "||---------- 6.Sort the ring ----------||" << endl;
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
				ring.PrintRing();
				system("pause");
				break;
			}
			case 2:
			{
				T value;
				cin >> value;
				ring.push(value);
				break;
			}
			case 3:
			{
				ring.PrintRing();
				if (ring.IsNotEmpty())
				{
					int n;
					cout << "\n\nEnter the number of the element: ";
					n = InInt(1, ring.getsize());
					ring.DeleteOneNode(n);
					ring.PrintRing();
					system("pause");
				}
				else system("pause");
				break;
			}
			case 4:
			{
				deleteby(ring);
				break;
			}
			case 5:
			{
				ring.DeleteRing();
				cout << "\nSuccess!\n";
				system("pause");
				break;
			}
			case 6:
			{
				sort(ring);
				break;
			}
			case 7:
			{
				find(ring);
				break;
			}
			case 8:
			{
				file(ring);
				break;
			}
			}
		} while (vflag);
	}
	
	void file(Ring<T>& ring)
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
					ring.ReadText();
				else ring.ReadBin();
				flag++;
				break;
			}
			case 2:
			{
				if (hflag == 1)
					ring.WriteText();
				else ring.WriteBin();
				flag++;
				break;
			}
			}
		} while (!flag);
	}

	void sort(Ring<T>& ring)
	{
		if (!ring.IsNotEmpty())
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
				alg.Sort(ring.gethead(), ring.gettail(), sortyear);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case 2:
				alg.Sort(ring.gethead(), ring.gettail(), sortprice);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case 3:
				alg.Sort(ring.gethead(), ring.gettail(), sortname);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case 4:
				alg.Sort(ring.gethead(), ring.gettail(), sortbrand);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			}
		} while (vflag);
	}

	void find(Ring<T>& ring)
	{
		if (!ring.IsNotEmpty())
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
				alg.Find(ring.gethead(), ring.gettail(), compyear);
				cout << endl;
				system("pause");
				break;
			case 2:
				alg.Find(ring.gethead(), ring.gettail(), compprice);
				cout << endl;
				system("pause");
				break;
			case 3:
				alg.Find(ring.gethead(), ring.gettail(), compname);
				cout << endl;
				system("pause");
				break;
			case 4:
				alg.Find(ring.gethead(), ring.gettail(), compbrand);
				cout << endl;
				system("pause");
				break;
			}
		} while (!flag);
	}

	//void find(Ring<T>& ring)
	//{
	//	if (!ring.IsNotEmpty())
	//	{
	//		cout << "The list is empty!\n\n";
	//		system("pause");
	//		return;
	//	}

	//	Ring<T> temp;
	//	Algorithms<T> alg;

	//	ring.PrintRing();

	//	cout << "'ESC' - to turn back" << endl;
	//	cout << "1. Enter the year" << endl;
	//	cout << "2. Enter the price" << endl;
	//	cout << "3. Enter the name" << endl;
	//	cout << "4. Enter the brand" << endl;

	//	switch (_getch())
	//	{
	//	case 27:
	//		return;
	//	case '1':
	//		temp = alg.Find(ring, compyear);
	//		if (temp.IsNotEmpty())
	//			find(temp);
	//		system("pause");
	//		break;
	//	case '2':
	//		temp = alg.Find(ring, compprice);
	//		if (temp.IsNotEmpty())
	//			find(temp);
	//		break;
	//	case '3':
	//		temp = alg.Find(ring, compname);
	//		if (temp.IsNotEmpty())
	//			find(temp);
	//		break;
	//	case '4':
	//		temp = alg.Find(ring, compbrand);
	//		if (temp.IsNotEmpty())
	//			find(temp);
	//		break;
	//	}
	//}


	void deleteby(Ring<T>& ring)
	{
		if (!ring.IsNotEmpty())
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
				alg.DeleteBy(ring, compyear);
				break;
			case 2:
				alg.DeleteBy(ring, compprice);
				break;
			case 3:
				alg.DeleteBy(ring, compname);
				break;
			case 4:
				alg.DeleteBy(ring, compbrand);
				break;
			}
		} while (!flag);
	}
};
