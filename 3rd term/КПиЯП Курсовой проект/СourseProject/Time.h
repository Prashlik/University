#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class Time
{
private:

	int h, m;

public:

	Time()
	{
		h = 0;
		m = 0;
	}

	Time(double time)
	{
		h = (int)time;
		m = (int)((time - h) * 100);
	}

	Time(const Time& time)
	{
		h = time.h;
		m = time.m;
	}

	~Time() {}

	Time& now();
	int geth();
	int getm();
	void seth(int newh);
	void setm(int newm);

	Time operator-(Time& sub);
	Time operator+(Time& add);
	Time& operator-=(Time& sub);
	Time& operator+=(Time& add);
	Time& operator=(double time);
	Time& operator=(const Time& time);

	bool operator>(Time time);
	bool operator<(Time time);
	bool operator>=(Time time);
	bool operator<=(Time time);
	bool operator==(Time time);
	bool operator!=(Time time);

	friend istream& operator>>(istream& stream, Time& T);
	friend ostream& operator<<(ostream& stream, Time& T);
	friend ifstream& operator>>(ifstream& stream, Time& T);
	friend ofstream& operator<<(ofstream& stream, Time& T);
};