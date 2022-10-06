#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <conio.h>
#include "header.h"

using namespace std;

String* add(String* mas, int size)
{
	String* NewStr = new String[size];

	for (int i = 0;i < size - 1;i++)
		NewStr[i] = mas[i];

	return NewStr;
}

int main()
{
	char op;
	int flag = 0, a = 0, b = 0, c = 0;
	int size = 2, len = 0;
	String* mas = new String[2];
	String aa;

	cout << "Enter the the first string: ";
	mas[0].setstring();
	
	cout << "\nEnter the second string: ";
	mas[1].setstring();

	do {
		system("CLS");

		cout << "Your strings:\n\n";

		for (int i = 0;i < size;i++)
		{
			cout << i << ")	";
			mas[i].getstring();
		}

		cout << "\n 1.Add a new string\n 2.Put strings together\n 3.Compare your strings\n 4.Highliht a substring\n 0.Exit\n\n";

		switch (_getch())
		{
		case '1':

			size++;

			mas = add(mas, size);

			cout << "\nEnter the string: ";
			mas[size - 1].setstring();

			break;

		case '2':

			cout << "Choose the first row (0.." << size - 1 << "): ";
			do
			{
				rewind(stdin);
				cin >> a;				
			} while (a < 0 || a >= size);

			cout << "Choose the second row (0.." << size - 1 << "): ";
			do
			{
				rewind(stdin);
				cin >> b;				
			} while (b < 0 || b >= size);
			
			cout << "Choose the way:\n 1.'+'   2.'+='\n";
			
			do {
				switch (op = _getch())
				{
				case '1':

					cout << "mas[a] + mas[b] = ";
					//mas[a] = mas[a] + mas[b];
					
					aa = mas[a] + mas[b];
					aa.getstring();

					break;

				case '2':

					cout << "mas[a] += mas[b] = ";
					mas[a] += mas[b];
					mas[a].getstring();

					break;

				default:

					cout << "\n\nUnknown command!\n\n";

					break;
				}

			} while (op > '2' && op < '1');

			system("PAUSE");
			break;

		case '3':

			cout << "Choose the first string (0.." << size - 1 << "): ";
			do
			{
				rewind(stdin);
				cin >> a;
			} while (a < 0 || a >= size);

			cout << "Choose the second string (0.." << size - 1 << "): ";
			do
			{
				rewind(stdin);
				cin >> b;
			} while (b < 0 || b >= size);

			cout << "\nstr[a] == str b  ----";
			if (mas[a] == mas[b]) cout << "True";
			else cout << "False";

			cout << "\nstr[a] != str b  ----";
			if (mas[a] != mas[b]) cout << "True";
			else cout << "False";

			cout << "\nstr[a] > str b  ----";
			if (mas[a] > mas[b]) cout << "True";
			else cout << "False";

			cout << "\nstr[a] < str b  ----";
			if (mas[a] < mas[b]) cout << "True\n";
			else cout << "False\n";

			system("PAUSE");

			break;

		case '4':

			cout << "Choose the string (0.." << size - 1 << "): ";
			do
			{
				rewind(stdin);
				cin >> a;
			} while (a < 0 || a >= size);

			cout << "Enter the first position: ";
			cin >> b;

			cout << "Enter the second position: ";
			cin >> c;

			mas[a](b, c).getstring();

			system("PAUSE");

			break;

		case '0':
			flag = 1;
			break;

		default:

			cout << "\n\nUnknown command!\n\n";

			system("PAUSE");

			break;
		}



	} while (flag != 1);
}