#include "Header.h"

int main()
{
	Laptop l;
	Smartphone s;
	Monoblock m;
	SysBlock sb;

	cin >> l;
	system("cls");
	l.table();
	cout << endl << l << endl;
	system("pause");

	system("CLS");
	cin >> s;
	system("cls");
	s.table();
	cout << endl << s << endl;
	system("pause");

	system("CLS");
	cin >> m;
	system("cls");
	m.table();
	cout << endl << m << endl;
	system("pause");

	system("CLS");
	cin >> sb;
	system("cls");
	sb.table();
	cout << endl << sb << endl;
	system("pause");



};