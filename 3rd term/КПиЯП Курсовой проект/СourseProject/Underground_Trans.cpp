#include "Underground_Trans.h"

void Underground_Trans::setstops(vector<class Underground_Stops*> st)
{
	stops = st;
}
void Underground_Trans::pushstops(class Underground_Stops* st)
{
	stops.push_back(st);
}
void Underground_Trans::setinterval(Time t)
{
	interval = t;
}
void Underground_Trans::setwinterval(Time t)
{
	winterval = t;
}

vector<class Underground_Stops*> Underground_Trans::getstops()
{
	return stops;
}
Time Underground_Trans::getinterval()
{
	return interval;
}
Time Underground_Trans::getwinterval()
{
	return winterval;
}

void Underground_Trans::info()
{
	cout << "||=============== Line # " << setw(3) << number << " ================||" << endl;
	cout << "||---------------- Interval: ----------------||" << endl;
	cout << "|| on weekdays: " << interval << "   on weekends: " << winterval << setw(7) << "||" << endl;
	for (int i = 0;i < stops.size();i++)
		cout << "||" << setw(4) << i + 1 << '.' << stops[i]->getname() << setw(40 - stops[i]->getname().size()) << "||" << endl;
	cout << "||===========================================||" << endl;
}

Underground_Trans& Underground_Trans::operator=(Underground_Trans& trans)
{
	stops = trans.stops;
	number = trans.number;
	st = trans.st;
	interval = trans.interval;
	winterval = trans.winterval;

	return *this;
}
bool Underground_Trans::operator>(Underground_Trans& T)
{
	if (number > T.number)
		return true;
	else return false;
}
bool Underground_Trans::operator<(Underground_Trans& T)
{
	if (number < T.number)
		return true;
	else return false;
}

istream& operator>>(istream& stream, Underground_Trans& T)
{
	stream >> dynamic_cast<Transport&> (T);

	cout << "Enter the interval of arriving on weekdays: \n";
	cout << "\n(The input format must be like: hh.mm)" << endl;

	T.interval = InTime(1.00);

	cout << "Enter the interval of arriving on weekends: \n";
	cout << "\n(The input format must be like: hh.mm)" << endl;

	T.winterval = InTime(1.00);

	return stream;
}
ostream& operator<<(ostream& stream, Underground_Trans& T)
{
	stream << "||" << setw(4) << T.getnumber() << '.' << T.stops[0]->getname() << " - " << T.stops[T.stops.size() - 1]->getname();
	stream << setw(38 - T.stops[0]->getname().size() - T.stops[T.stops.size() - 1]->getname().size()) << "||" << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Underground_Trans& T)
{
	stream << dynamic_cast<Transport&> (T);
	stream << T.interval;
	stream << T.winterval;
	return stream;
}
ifstream& operator>>(ifstream& stream, Underground_Trans& T)
{
	stream >> dynamic_cast<Transport&> (T);
	stream >> T.interval;
	stream >> T.winterval;
	return stream;
}