#pragma once
#include "Header.h"
#include "Template.h"


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
		T value;
		int n;
		bool flag = 0;
		do
		{
			rewind(stdin);
			system("cls");
			cout << "============= MENU ===============" << endl;
			cout << "||   [Esc] - Exit the program   ||" << endl;
			cout << "||1.Show your ring              ||" << endl;
			cout << "||2.Add a new element           ||" << endl;
			cout << "||3.Delete an element           ||" << endl;
			cout << "||4.Delete the ring             ||" << endl;
			cout << "||5.Sort by year                ||" << endl;
			cout << "||6.Sort by price               ||" << endl;
			cout << "||7.Sort by name                ||" << endl;
			cout << "||8.Sort by brand               ||" << endl;
			cout << "||==============================||" << endl;
			switch (_getch())
			{
			case 27:

				flag++;
				break;

			case '1':

				ring.PrintRing(); 
				system("pause");
				break;

			case '2':

				cin >> value;
				ring.push(value);
				break;

			case '3':

				cout << "Enter the number of the element: "; 
				do {
					cin >> n;
					if (n < 0 || n > ring.getsize())
						cout << "Invalid input! Please, try again." << endl;
				} while (n < 0 || n > ring.getsize());
				ring.DeleteOneNode(n);
				ring.PrintRing(); 
				system("pause");
				break;

			case '4':

				ring.DeleteRing();
				system("pause");
				break;

			case '5':

				ring.sort(CompYear); 
				cout << endl;
				ring.PrintRing(); 
				system("pause");
				break;

			case '6':

				ring.sort(CompPrice); 
				cout << endl;
				ring.PrintRing(); 
				system("pause");
				break;

			case '7':

				ring.sort(CompName);
				cout << endl;
				ring.PrintRing(); 
				system("pause");
				break;

			case '8':

				ring.sort(CompBrand);
				cout << endl;
				ring.PrintRing();
				system("pause");
				break;

			}
		} while (!flag);
	}
};