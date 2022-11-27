#include "Transport.h"

void Transport::setnumber(int num)
{
	number = num;
}
void Transport::setst(vector<int> s)
{
	st = s;
}
void Transport::pushst(int s)
{
	st.push_back(s);
}

unsigned int Transport::getnumber()
{
	return number;
}
vector<int> Transport::getst()
{
	return st;
}

Transport& Transport::operator=(Transport& trans)
{
	number = trans.number;

	return *this;
}

istream& operator>>(istream& stream, Transport& T)
{
	return stream;
}
ostream& operator<<(ostream& stream, Transport& T)
{
	stream << "||================ Route ¹" << setw(3) << T.number <<" ================||" << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Transport& T)
{
	int size;
	stream << setw(5) << T.number;
	size = T.st.size();
	stream << setw(5) << size;
	for (int i = 0; i < size; i++)
		stream << setw(5) << T.st[i];
	return stream;
}
ifstream& operator>>(ifstream& stream, Transport& T)
{
	int size;
	stream >> T.number;
	stream >> size;
	T.st.resize(size);
	for (int i = 0; i < size; i++)
		stream >> T.st[i];
	return stream;
}
