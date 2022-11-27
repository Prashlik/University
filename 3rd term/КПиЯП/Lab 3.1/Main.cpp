#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"

using namespace std;

int main()
{
	char s[80];

	cout << "Enter the first string: ";
	gets_s(s);

	String a(s);

	cout << "Enter the second string: ";
	gets_s(s);

	String b(s);

	cout << "Enter the third string: ";
	gets_s(s);

	String c(s);

	cout << "a + b = ";
	String result1(a + b);
	result1.getstring();

	cout << "\nb + c = ";
	String result2;
	result2 = b + c;
	result2.getstring();

	cout << "\n";

	String result3("123456");
	result2 += result1 + "! 123" + a + b + '!\n';
	result3 += "asd";
	result3.getstring();

}
