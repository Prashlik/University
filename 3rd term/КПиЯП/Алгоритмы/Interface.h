#pragma once
#include "Header.h"
#include "Template.h"
#include "Algorithms.h"


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

			cout << "0.Exit the program" << endl;
			cout << "1.Create a ring of the smartphones" << endl;
			cout << "2.Create a ring of the laptops" << endl;
			cout << "3.Create a ring of the system blocks" << endl;
			cout << "4.Create a ring of the monoblocks" << endl;

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
		bool flag = 0;
		do
		{
			rewind(stdin);
			system("cls");
			cout << "============== MENU ===============" << endl;
			cout << "||   [Esc] - Exit the program    ||" << endl;
			cout << "||1.Show your ring               ||" << endl;
			cout << "||2.Add a new element            ||" << endl;
			cout << "||3.Delete an element by number  ||" << endl;
			cout << "||4.Delete the element(s) by data||" << endl;
			cout << "||5.Delete the ring              ||" << endl;
			cout << "||6.Sort the ring                ||" << endl;
			cout << "||7.Find the element(s)          ||" << endl;
			cout << "||===============================||" << endl;
			switch (_getch())
			{
			case 27:

				flag++;
				break;

			case '1':
			{
				ring.PrintRing();
				system("pause");
				break;
			}
			case '2':
			{
				T value;
				cin >> value;
				ring.push(value);
				break;
			}
			case '3':
			{
				ring.PrintRing();
				if (ring.IsNotEmpty())
				{
					int n;
					cout << "\n\nEnter the number of the element: ";
					do {
						cin >> n;
						if (n < 0 || n > ring.getsize())
							cout << "Invalid input! Please, try again." << endl;
					} while (n < 0 || n > ring.getsize());
					ring.DeleteOneNode(n);
					ring.PrintRing();
					system("pause");
				}
				else system("pause");
				break;
			}
			case '4':
			{
				deleteby(ring);
				break;
			}
			case '5':
			{
				ring.DeleteRing();
				cout << "\nSuccess!\n";
				system("pause");
				break;
			}
			case '6':
			{
				sort(ring);
				break;
			}
			case '7':
			{
				find(ring);
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
		bool flag = 0;
		do
		{
			rewind(stdin);
			system("cls");
			cout << "============== MENU ===============" << endl;
			cout << "||       [Esc] - turn back       ||" << endl;
			cout << "||1.Sort by year                 ||" << endl;
			cout << "||2.Sort by price                ||" << endl;
			cout << "||3.Sort by name                 ||" << endl;
			cout << "||4.Sort by brand                ||" << endl;
			cout << "||===============================||" << endl;
			switch (_getch())
			{
			case 27:
				flag++;
				break;
			case '1':
				alg.Sort(ring.gethead(), ring.gettail(), sortyear);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case '2':
				alg.Sort(ring.gethead(), ring.gettail(), sortprice);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case '3':
				alg.Sort(ring.gethead(), ring.gettail(), sortname);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			case '4':
				alg.Sort(ring.gethead(), ring.gettail(), sortbrand);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;
			}
		} while (!flag);
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
		bool flag = 0;
		do
		{
			rewind(stdin);
			system("cls");
			cout << "============== MENU ===============" << endl;
			cout << "||       [Esc] - turn back       ||" << endl;
			cout << "||1.Find by year                 ||" << endl;
			cout << "||2.Find by price                ||" << endl;
			cout << "||3.Find by name                 ||" << endl;
			cout << "||4.Find by brand                ||" << endl;
			cout << "||===============================||" << endl;
			switch (_getch())
			{
			case 27:
				flag++;
				break;
			case '1':
				alg.Find(ring.gethead(), ring.gettail(), compyear);
				cout << endl;
				system("pause");
				break;
			case '2':
				alg.Find(ring.gethead(), ring.gettail(), compprice);
				cout << endl;
				system("pause");
				break;
			case '3':
				alg.Find(ring.gethead(), ring.gettail(), compname);
				cout << endl;
				system("pause");
				break;
			case '4':
				alg.Find(ring.gethead(), ring.gettail(), compbrand);
				cout << endl;
				system("pause");
				break;
			}
		} while (!flag);
	}

	void deleteby(Ring<T>& ring)
	{
		if (!ring.IsNotEmpty())
		{
			cout << "The list is empty!\n\n";
			system("pause");
			return;
		}

		Algorithms<T> alg;
		bool flag = 0;
		do
		{
			rewind(stdin);
			system("cls");
			cout << "============== MENU ===============" << endl;
			cout << "||      [Esc] - turn back        ||" << endl;
			cout << "||1.Delete by year               ||" << endl;
			cout << "||2.Delete by price              ||" << endl;
			cout << "||3.Delete by name               ||" << endl;
			cout << "||4.Delete by brand              ||" << endl;
			cout << "||===============================||" << endl;
			switch (_getch())
			{
			case 27:
				flag++;
				break;
			case '1':
				alg.DeleteBy(ring, compyear);
				break;
			case '2':
				alg.DeleteBy(ring, compprice);
				break;
			case '3':
				alg.DeleteBy(ring, compname);
				break;
			case '4':
				alg.DeleteBy(ring, compbrand);
				break;
			}
		} while (!flag);
	}
};
