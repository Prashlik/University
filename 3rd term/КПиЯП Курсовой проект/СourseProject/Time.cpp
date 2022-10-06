#include "Time.h"

Time& Time::now()
{
	struct tm ltm;
	time_t now = time(0);
	localtime_s(&ltm, &now);

	h = ltm.tm_hour;
	m = ltm.tm_min;

	return *this;
}
int Time::geth()
{
	return h;
}
int Time::getm()
{
	return m;
}
void Time::seth(int newh)
{
	h = newh;
}
void Time::setm(int newm)
{
	m = newm;
}

Time Time::operator-(Time& sub)
{
	Time temp;
	temp.m -= sub.m;

	if (temp.m < 0)
	{
		temp.h--;
		temp.m += 60;
	}

	temp.h -= sub.h;

	if (temp.h < 0)
	{
		temp.h += 24;
	}

	return temp;
}
Time Time::operator+(Time& add)
{
	Time temp = *this;

	temp.h += add.h;
	temp.m += add.m;

	if (temp.m >= 60)
	{
		temp.h++;
		temp.m -= 60;
	}
	if (temp.h >= 24)
	{
		temp.h -= 24;
	}

	return temp;
}
Time& Time::operator-=(Time& sub)
{
	m -= sub.m;

	if (m < 0)
	{
		h--;
		m += 60;
	}

	h -= sub.h;

	if (h < 0)
	{
		h += 24;
	}

	return *this;
}
Time& Time::operator+=(Time& add)
{
	h += add.h;
	m += add.m;

	if (m >= 60)
	{
		h++;
		m -= 60;
	}
	if (h >= 24)
	{
		h -= 24;
	}

	return *this;
}
Time& Time::operator=(double time)
{
	time += 0.001;
	h = (int)time;
	m = (int)((time - h) * 100);

	return *this;
}
Time& Time::operator=(const Time& time)
{
	h = time.h;
	m = time.m;

	return *this;
}

bool Time::operator>(Time time)
{
	bool flag = 0;

	if (h > time.h && ((h > 5 && time.h > 5) || (h <= 5 && time.h <= 6)))
		flag = 1;
	else if (h < 5 && time.h > 5)
		flag = 1;
	else if (h == time.h && m > time.m)
		flag = 1;

	return flag;
}
bool Time::operator<(Time time)
{
	bool flag = 0;

	if (h < time.h && ((h > 5 && time.h > 5) || (h <= 5 && time.h <= 5)))
		flag = 1;
	else if (h > 5 && time.h < 5)
		flag = 1;
	else if (h == time.h && m < time.m)
		flag = 1;

	return flag;
}
bool Time::operator>=(Time time)
{
	bool flag = 0;

	if (h == time.h && m >= time.m)
		flag = 1;
	else if (h > time.h && ((h > 5 && time.h > 5) || (h <= 5 && time.h <= 5)))
		flag = 1;
	else if (h < 5 && time.h > 5)
		flag = 1;

	return flag;
}
bool Time::operator<=(Time time)
{
	bool flag = 0;

	if (h == time.h && m <= time.m)
		flag = 1;
	else if (h < time.h && ((h > 5 && time.h > 5) || (h <= 5 && time.h <= 5)))
		flag = 1;
	else if (h > 5 && time.h < 5)
		flag = 1;

	return flag;
}
bool Time::operator==(Time time)
{
	bool flag = 0;

	if (h == time.h && m == time.m)
		flag = 1;

	return flag;
}
bool Time::operator!=(Time time)
{
	bool flag = 0;

	if (h != time.h || m != time.m)
		flag = 1;

	return flag;
}

istream& operator>>(istream& stream, Time& T)
{
	double time;
	stream >> time;

	T.h = (int)time;
	T.m = (int)((time - T.h) * 100);

	return stream;
}
ostream& operator<<(ostream& stream, Time& T)
{
	stream << T.h << ':';
	if (T.m < 10)
		stream << 0;
	stream << T.m;

	return stream;
}
ifstream& operator>>(ifstream& stream, Time& T)
{
	double time;
	stream >> time;

	T.h = (int)time;
	T.m = (int)((time - T.h) * 100);

	return stream;
}
ofstream& operator<<(ofstream& stream, Time& T)
{
	stream << setw(4) << T.h << '.';
	if (T.m < 10)
		stream << 0;
	stream << T.m;

	return stream;
}