#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string.h>
#include <cstdio>
#include "header.h"

String& String::operator=(const String& str2)
{
	str = str2.str;
	length = str2.length;

	return *this;
}

String& String::operator+=(String& str2)
{
	strcat(str, str2.str);
	length += str2.length;

	return *this;
}

String& String::operator+=(char* str2)
{
	strcat(str, str2);
	length += strlen(str2);

	return *this;
}

String String::operator+(const String str2)
{
	String NewString;

	strcpy(NewString.str, str);
	strcat(NewString.str, str2.str);

	NewString.length = length + str2.length;

	return NewString;
}

String& String::operator+(char* str2)
{
	String* NewString = new String;

	strcpy(NewString->str, str);
	strcat(NewString->str, str2);

	NewString->length = length + strlen(str2);

	return *NewString;
}

char& String::operator[](int i)
{
	return str[i];
}

String String::operator()(int a, int b)
{
	String res;
	int n = 0;

	for (int i = a;i <= b;i++)
	{
		res.str[n] = str[i];
		n++;
	}

	res[n] = '\0';

	return res;
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
	puts(str);
}

void String::setstring()
{
	gets_s(str, 256);
	length = strlen(str);
}