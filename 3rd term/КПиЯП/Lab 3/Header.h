#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>

class String
{
	char* str;
	int length;

public:

	explicit String(int len = 256)
	{
		length = len;
		str = new char[length];
	}

	String(String& str2)
	{
		strcpy(str, str2.str);
		length = str2.length;		
	}

	//explicit String(int len)
	//{
	//	length = len;
	//	str = new char[length + 1];
	//	str[length] = '\0';
	//}

	~String()
	{
		delete[] str;
	}

	void setstring();
	void getstring();

	String& operator=(const String&);
	String operator+(const String);
	String& operator+(char*);
	String& operator+=(String&);
	String& operator+=(char*);

	int operator==(String&);
	int operator!=(String&);
	int operator>(String&);
	int operator<(String&);

	char& operator[](int);
	String operator()(int, int);

};