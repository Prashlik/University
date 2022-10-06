#include <iostream>
#include <conio.h>
#include "header.h"

using namespace std;

int main()
{
	int len = 0;

	cout << "Enter the size of the first row: ";
	cin >> len;
	row firstrow(len);
	firstrow.setrow();
	cout << "\nEnter the size of the second row: ";
	cin >> len;
	row secrow(len);
	secrow.setrow();

	row thirdrow, fourthrow;

	cout << "firstrow + secrow = thirdrow:\n";
	thirdrow = firstrow.sum(secrow);
	thirdrow.getrow();

	cout << "firstrow - secrow = fourthrow:\n";
	fourthrow = firstrow.sub(secrow);
	fourthrow.getrow();
}