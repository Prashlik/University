#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"

using namespace std;

String& String::operator=(const String& str2)
{
	if (str != 0)
		delete[] str;

	str = new char[str2.length + 1];

	strcpy_s(str, str2.length + 1, str2.str);
	length = str2.length;

	return *this;
}

String& String::operator+=(const String& str2)
{
	*this = *this + str2;
	/*char* NewString;
	int NewLength = length + str2.length;
	NewString = new char[NewLength + 1];

	int i = 0;
	for (; i < length;i++)
		NewString[i] = str[i];

	for (int j = 0; i < NewLength;i++, j++)
		NewString[i] = str2.str[j];

	NewString[NewLength] = '\0';

	length = NewLength;

	delete[] str;

	str = NewString;*/

	return *this;
}

String& String::operator+=(const char* str2)
{
	*this = *this + str2;

	/*char* NewString;
	int NewLength = length + strlen(str2);
	NewString = new char[NewLength + 1];

	int i = 0;
	for (; i < length;i++)
		NewString[i] = str[i];

	for (int j = 0; i < NewLength;i++, j++)
		NewString[i] = str2[j];

	NewString[NewLength] = '\0';

	length = NewLength;

	delete[] str;

	str = NewString;*/

	return *this;
}

String& String::operator+=(const char str2)
{
	*this = *this + str2;

	/*char* NewString;
	int NewLength = length + 1;
	NewString = new char[NewLength + 1];

	int i = 0;
	for (; i < length;i++)
		NewString[i] = str[i];

	NewString[i] = str2;

	NewString[NewLength] = '\0';

	length = NewLength;

	delete[] str;

	str = NewString;*/

	return *this;
}

String String::operator+(const String& str2)
{
	String NewString;
	NewString.length = length + str2.length;
	NewString.str = new char[NewString.length + 1];	

	int i = 0;
	for (; i < length;i++)
		NewString.str[i] = str[i];

	for (int j = 0; i < NewString.length;i++, j++)
		NewString.str[i] = str2.str[j];


	NewString.str[NewString.length] = '\0';


	return NewString;
}

String String::operator+(const char* str2)
{
	String NewString;
	NewString.length = length + strlen(str2);
	NewString.str = new char[NewString.length + 1];

	int i = 0;
	for (; i < length;i++)
		NewString.str[i] = str[i];

	for (int j = 0; i < NewString.length;i++, j++)
		NewString.str[i] = str2[j];

	NewString.str[NewString.length] = '\0';

	return NewString;
}

String String::operator+(const char str2)
{
	String NewString;
	NewString.length = length + 1;
	NewString.str = new char[NewString.length + 1];

	int i = 0;
	for (; i < length;i++)
		NewString.str[i] = str[i];

	NewString.str[i] = str2;

	NewString.str[NewString.length] = '\0';

	return NewString;
}

String operator+(const char* str1, const String& str2)
{
	String NewString;
	NewString.length = strlen(str1) + str2.length;
	NewString.str = new char[NewString.length + 1];

	int i = 0;
	for (; i < strlen(str1);i++)
		NewString.str[i] = str1[i];

	for (int j = 0; i < NewString.length;i++, j++)
		NewString.str[i] = str2.str[j];

	NewString.str[NewString.length] = '\0';

	return NewString;
}

char& String::operator[](int i)
{
	return str[i];
}

String String::operator()(int a, int b)
{
	String NewString;
	NewString.length = b - a + 1;
	NewString.str = new char[NewString.length + 1];

	int n = 0;

	for (int i = a;i <= b;i++)
	{
		NewString.str[n] = str[i];
		n++;
	}

	NewString[n] = '\0';

	return NewString;
}

int String::operator==(String& str2)
{
	for (int i = 0;str[i - 1] != '\0' && str2[i - 1] != '\0';i++)
	{
		if (str[i] != str2[i])
			return 0;
	}

	return 1;
}

int String::operator!=(String& str2)
{
	for (int i = 0;str[i - 1] != '\0' && str2[i - 1] != '\0';i++)
	{
		if (str[i] != str2[i])
			return 1;
	}

	return 0;
}

int String::operator>(String& str2)
{
	if (strlen(str) > strlen(str2.str))
		return 1;
	return 0;
}

int String::operator<(String& str2)
{
	if (strlen(str) < strlen(str2.str))
		return 1;
	return 0;
}

void String::getstring()
{
	cout << str;;
}

void String::setstring()
{
	if (length != 0) return;

	char s[80];
	fgets(s, 80, stdin);

	length = strlen(s);

	str = new char[length + 1];
	strcpy_s(str, sizeof(length) + 1, s);
}