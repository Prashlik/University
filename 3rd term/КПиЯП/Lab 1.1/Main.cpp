#include <iostream>
#include <conio.h>
#include "header.h"

using namespace std;

row* add(row* Arr, int size)
{
	row* NewArr = new row[size];

	for (int i = 0;i < size - 1;i++)
		NewArr[i] = Arr[i];

	delete[] Arr;

	return NewArr;
}

int main()
{
	char op;
	int flag = 0;
	vector <row> mas;
	int size = 2, int len = 0;

	cout << "Enter the size of the first row: ";
	cin >> len;
	row a(len);
	mas[0] = a;
	cout << "\nEnter the size of the second row: ";
	cin >> len;
	row b(len);
	mas[0] = a;
	
	do {
		rewind(stdin);
		cout << "1.Add a new row\n 2.Show all\n 3.Do calculations\n 0.Exit";
		
		switch (op = getch())
		{
		case '1':

			size++;
			Mas = add(Mas, size);

			break;

		case '2':

			for (int i = 0;i < size;i++)
				Mas[i].getrow();

			break;

		case '3':

			cout << "What calculations do you want to do?\n   1.Summation\n   2.Subtraction";
			do {
				switch (op = getch())
				{
				case '1':

					break;

				case '2':

					break;
				}

			} while (op > '2' && op < '1');



			break;

		case '0':
			flag = 1;
			break;

		default:

			break;
		}



	} while (flag != 1);
}