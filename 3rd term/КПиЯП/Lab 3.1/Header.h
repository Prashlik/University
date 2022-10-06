#pragma once
#include <cstring>

class String
{
	char* str;
	int length;

public:

	String()
	{
		length = 0;
		str = nullptr;
	}

	String(const char* str2)
	{
		length = strlen(str2);

		str = new char[length + 1];
		strcpy_s(str, length + 1, str2);
	}

	//explicit String(const char* str2)
	//{
	//	length = strlen(str2);

	//	str = new char[length + 1];
	//	strcpy(str, str2);
	//}

	String(const String& str2)
	{
		length = str2.length;

		str = new char[length + 1];
		strcpy_s(str, str2.length + 1, str2.str);
	}

	~String()
	{
		delete[] str;
	}

	void setstring();
	void getstring();

	String& operator=(const String&);
	String operator+(const String&);
	String operator+(const char*);
	String operator+(const char);
	friend String operator+(const char*,const String&);
	String& operator+=(const String&);
	String& operator+=(const char*);
	String& operator+=(const char);

	int operator==(String&);
	int operator!=(String&);
	int operator>(String&);
	int operator<(String&);

	char& operator[](int);
	String operator()(int, int);

};