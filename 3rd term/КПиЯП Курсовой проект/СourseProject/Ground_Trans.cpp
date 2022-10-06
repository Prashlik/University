#include "Ground_Trans.h"

using namespace std;

void Ground_Trans::setstops(Ring<Ground_Stops*> st)
{
	stops = st;
}
void Ground_Trans::settime1(vector<Time> t1)
{
	time1 = t1;
}
void Ground_Trans::settime2(vector<Time> t2)
{
	time2 = t2;
}
void Ground_Trans::setwtime1(vector<Time> t1)
{
	wtime1 = t1;
}
void Ground_Trans::setwtime2(vector<Time> t2)
{
	wtime2 = t2;
}
void Ground_Trans::pushstops(class Ground_Stops* st)
{
	stops.push(st);
}
void Ground_Trans::delstops(int type)
{
	for (int i = 0;i < stops.getsize();i++)
	{
		int j;
		Ring<Ground_Trans*> tr = stops[i]->gettrans(type);
		for (j = 0;j < tr.getsize();j++)
			if (tr[j]->getnumber() == number)
				break;
		tr.DeleteNode(j);
		stops[i]->settrans(type, tr);
	}

	stops.Delete();
	st.clear();
}
void Ground_Trans::setstops(Ring<Ground_Stops>& gs, int type)
{
	int num, i, k = 0, t = 0, f;

	delstops(type);

	cout << "Enter the id of the first station(from " << 1 << " to " << gs.getsize() << "): ";

	for (i = 1; i < gs.getsize();i++)
		if (gs[i].getid() > k) k = gs[i].getid();
	do {
		f = 0;
		num = InInt(1, k);
		for (i = 0; i < gs.getsize();i++)
			if (num == gs[i].getid())
			{
				f++;
				break;
			}
		if (!f) cout << "There are no stops with the same id, please try again: ";
	} while (!f);

	do
	{
		int id;
		if (t)
			id = gs[t].getid();
		else id = -1;
		t = i;

		stops.push(&gs[i]);
		st.push_back(num);

		gs[t].pushtrans(type, this);

		vector<Nearest_St> ns = gs[t].getnstops();
		cout << "Enter the id of the next station (";
		for (int j = 0;j < ns.size();j++)
		{
			f = 0;
			for (int k = 0; k < st.size(); k++)
				if (st[k] == ns[j].id)
				{
					f = 1;
					break;
				}
			if (!f)
				cout << ns[j].id << ' ';
		}
		cout << ")\n(0 - end of entering): ";

		do {
			f = 0;
			num = InInt(0, k);
			for (int j = 0; j < st.size(); j++)
				if (st[j] == num)
				{
					f = -1;
					break;
				}
			if (f != -1)
				for (i = 0;i < ns.size();i++)
					if (num == ns[i].id)
					{
						f++;
						for (i = 0;gs[i].getid() != num;i++);
						break;
					}
			if ((!f) & num) cout << "There are no nearest stops with the same id, please try again: ";
		} while ((!f) & num);
		if (num == 0) break;
	} while (num);
}

Ring<Ground_Stops*> Ground_Trans::getstops()
{
	return stops;
}
vector<Time> Ground_Trans::gettime1()
{
	return time1;
}
vector<Time> Ground_Trans::gettime2()
{
	return time2;
}
vector<Time> Ground_Trans::getwtime1()
{
	return wtime1;
}
vector<Time> Ground_Trans::getwtime2()
{
	return wtime2;
}

vector<Time> Ground_Trans::fromtotime(bool a, bool b, int c) 
{
	vector<Time> NewTime;
	Time t;
	int d, i;
	if (a == 1)
	{
		d = -1;
		i = stops.getsize() - 1;
		if (b == 0)
			NewTime = time1;
		else NewTime = wtime1;
	}
	else
	{
		d = 1;
		i = 0;
		if (b == 0)
			NewTime = time2;
		else NewTime = wtime2;
	}


	for (i; stops[i]->getid() != c; i += d)
	{
		for (int l = 0; l < stops[i]->getnstops().size();l++)
			if (stops[i]->getnstops()[l].id == stops[i + d]->getid())
			{
				t = stops[i]->getnstops()[l].time;
				break;
			}
		for (int k = 0; k < NewTime.size();k++)
			NewTime[k] = NewTime[k] + t;
	}
	return NewTime;
}

Ground_Trans& Ground_Trans::operator=(Ground_Trans& trans)
{
	number = trans.number;
	st = trans.st;
	stops = trans.stops;
	time1 = trans.time1;
	time2 = trans.time2;
	wtime1 = trans.wtime1;
	wtime2 = trans.wtime2;

	return *this;
}
bool Ground_Trans::operator>(Ground_Trans& T)
{
	if (number > T.number)
		return true;
	else return false;
}
bool Ground_Trans::operator<(Ground_Trans& T)
{
	if (number < T.number)
		return true;
	else return false;
}

void Ground_Trans::info()
{
	int wday = 1;
	bool flag = 0, key = 0;
	int dir = 1;
	int d, i, size;
	Time now;
	now.now();

	struct tm ltm;
	time_t nw = time(0);
	localtime_s(&ltm, &nw);

	if (((ltm.tm_wday == 0) || ((ltm.tm_wday == 6) & (now.geth() > 5))) || ((ltm.tm_wday == 1) & (now.geth() < 5)))
		wday = 1;
	do {
		do {
			if (dir == 2)
			{
				d = -1;
				i = st.size() - 1;
				size = -1;
			}
			else
			{
				d = 1;
				i = 0;
				size = st.size();
			}
			system("cls");
			cout << "================= Route # " << setw(3) << number << " ==================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter' - to choose the number of the stop)||" << endl;
			if (wday == 1)
				cout << "||== ('Left', 'Right' - [weekday]/weekend) ===||" << endl;
			else
				cout << "||== ('Left', 'Right' - weekday/[weekend]) ===||" << endl;
			cout << "||== ('Up', 'Down' - change the direction) ===||" << endl;
			cout << "||                                            ||" << endl;

			for (i;i != size;i += d)
			{
				int k;
				int f = 0;
				cout << "|| " << setw(3) << i + 1 << ". " << stops[i]->getname() << setw(40 - stops[i]->getname().size()) << "||" << endl;
				vector<Time> t = fromtotime(dir - 1, wday - 1, stops[i]->getid());
				for (k = 0;k < t.size();k++)
					if (t[k] > now)
					{
						f = 1;
						break;
					}
				cout << "||";
				if (!f)
					cout << "   The route is over                        ||" << endl;
				else
				{
					int flag = 0;
					for (k;k < t.size() && flag != 3;k++, flag++)
						cout << setw(4) << t[k];
					cout << setw(46 - 7 * flag) << "||" << endl;
				}
			}
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::LEFT:
						if (wday == 1)
							wday = 2;
						else wday--;
						key++;
						break;
					case Keys::RIGHT:
						if (wday == 2)
							wday = 1;
						else wday++;
						key++;
						break;
					case Keys::UP:
						if (dir == 1)
							dir = 2;
						else dir--;
						key++;
						break;
					case Keys::DOWN:
						if (dir == 2)
							dir = 1;
						else dir++;
						key++;
						break;
					case Keys::ESC:
						dir = 0;
						flag++;
						key++;
						break;
					case Keys::ENTER:
					{
						int id, flag = 0;
						cout << "Enter the number of the stop: ";
						id = InInt(1, st.size());
						stopinfo(stops[i]->getid());
						key++;
						break;
					}
					}
				}
			} while (!key);
		} while (!flag);
	} while (dir);
}
void Ground_Trans::stopinfo(int id)
{
	int numb;
	int wday = 1;
	bool flag = 0, key = 0;
	int dir = 1;
	int d, i, size;
	Time now;
	now.now();

	struct tm ltm;
	time_t nw = time(0);
	localtime_s(&ltm, &nw);

	if ((ltm.tm_wday == 0 || ltm.tm_wday == 6 & now.geth() > 5) || (ltm.tm_wday == 1 & now.geth() < 5))
		wday = 1;

	for (i = 0; i < stops.getsize();i++)
		if (stops[i]->getid() == id)
			break;
	numb = i;

	do {
		do {
			if (dir == 2)
			{
				d = -1;
				i = st.size() - 1;
				size = 0;
			}
			else
			{
				d = 1;
				i = 0;
				size = st.size() - 1;
			}
			system("cls");
			cout << "================= Route # " << setw(3) << number << " ==================" << endl;
			cout << "============== " << stops[numb]->getname() << setw(33 - stops[numb]->getname().size()) << " ================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (wday == 1)
				cout << "||== ('Left', 'Right' - [weekday]/weekend) ===||" << endl;
			else
				cout << "||== ('Left', 'Right' - weekday/[weekend]) ===||" << endl;
			cout << "||== ('Up', 'Down' - change the direction) ===||" << endl;
			cout << "||  " << setw(15) << stops[i]->getname() << " - " << stops[size]->getname();
			cout << setw(26 - stops[size]->getname().size()) << "         ||" << endl;

			int k;
			int f = 0;
			vector<Time> t = fromtotime(dir - 1, wday - 1, id);
			for (k = 0; k < t.size(); k++)
			{
				f = 0;
				cout << "|| ";
				for (k;k < t.size() && f != 5;k++, f++)
					cout << setw(4) << t[k];
				cout << setw(45 - 7 * f) << "||" << endl;
			}

			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::LEFT:
						if (wday == 1)
							wday = 2;
						else wday--;
						key++;
						break;
					case Keys::RIGHT:
						if (wday == 2)
							wday = 1;
						else wday++;
						key++;
						break;
					case Keys::UP:
						if (dir == 1)
							dir = 2;
						else dir--;
						key++;
						break;
					case Keys::DOWN:
						if (dir == 2)
							dir = 1;
						else dir++;
						key++;
						break;
					case Keys::ESC:
						dir = 0;
						flag++;
						key++;
						break;
					}
				}
			} while (!key);
		} while (!flag);
	} while (dir);
}

istream& operator>>(istream& stream, Ground_Trans& T)
{
	Time t, first, last;
	int flag;

	T.time1.clear();
	T.time2.clear();
	T.wtime1.clear();
	T.wtime2.clear();

	{
		system("cls");

		cout << "Enter the departure times of the transport from the first station on weekdays:" << endl;
		cout << "Enter the time of the first time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;
		first = InTime(24);
		T.time1.push_back(first);
		cout << "\nEnter the time of the last time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;

		last = InTime(24);

		while (last < first)
		{
			cout << "This time must be more than" << first << endl;
			cout << "Please, try again: ";
			last = InTime(24);
		}

		flag = 0;
		cout << "\n1.Enter the interval";
		cout << "\n2.Enter the other times";
		do {
			switch (_getch())
			{
			case '1':
				flag = 1;
				break;
			case'2':
				flag = 2;
				break;
			}
		} while (!flag);

		if (flag == 1)
		{
			cout << "\n\nEnter the interval of departure: ";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			t = InTime(12);
			while (last > (first + t))
			{
				first += t;
				T.time1.push_back(first);
			}
			T.time1.push_back(last);
		}
		else
		{
			cout << "\nEnter the other times(the last time - the end of the entering):";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			do {

				t = InTime(24);
				if (t > first && t <= last)
				{
					T.time1.push_back(t);
					first = t;
				}
				else
				{
					cout << "Uncorrect input! Please, try again." << endl;
					cout << "The time must be more than " << first << " and less than " << last << endl;
				}
			} while (t != last);
		}

		system("cls");

		cout << "Enter the departure times of the transport from the last station on weekdays:" << endl;
		cout << "Enter the time of the first time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;
		first = InTime(24);
		T.time2.push_back(first);
		cout << "\nEnter the time of the last time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;

		last = InTime(24);

		while (last < first)
		{
			cout << "This time must be more than" << first << endl;
			cout << "Please, try again: ";
			last = InTime(24);
		}


		flag = 0;
		cout << "\n1.Enter the interval";
		cout << "\n2.Enter the other times";
		do {
			switch (_getch())
			{
			case '1':
				flag = 1;
				break;
			case'2':
				flag = 2;
				break;
			}
		} while (!flag);

		if (flag == 1)
		{
			cout << "\n\nEnter the interval of departure: ";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			t = InTime(12);
			while ((first + t) < last)
			{
				first += t;
				T.time2.push_back(first);
			}
			T.time2.push_back(last);
		}
		else
		{
			cout << "\nEnter the other times(the last time - the end of the entering):";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			do {

				t = InTime(24);
				if (t > first && t <= last)
				{
					T.time2.push_back(t);
					first = t;
				}
				else
				{
					cout << "Uncorrect choise! Please, try again." << endl;
					cout << "The time must be more than " << first << " and less than " << last << endl;
				}
			} while (t != last);
		}
	}
	{
		system("cls");

		cout << "Enter the departure times of the transport from the first station on weekends:" << endl;
		cout << "Enter the time of the first time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;
		first = InTime(24);
		T.wtime1.push_back(first);
		cout << "\nEnter the time of the last time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;

		last = InTime(24);

		while (last < first)
		{
			cout << "This time must be more than" << first << endl;
			cout << "Please, try again: ";
			last = InTime(24);
		}


		flag = 0;
		cout << "\n1.Enter the interval";
		cout << "\n2.Enter the other times";
		do {
			switch (_getch())
			{
			case '1':
				flag = 1;
				break;
			case'2':
				flag = 2;
				break;
			}
		} while (!flag);

		if (flag == 1)
		{
			cout << "\n\nEnter the interval of departure: ";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			t = InTime(12);
			while ((first + t) < last)
			{
				first += t;
				T.wtime1.push_back(first);
			}
			T.wtime1.push_back(last);
		}
		else
		{
			cout << "\nEnter the other times(the last time - the end of the entering):";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			do {

				t = InTime(24);
				if (t > first && t <= last)
				{
					T.wtime1.push_back(t);
					first = t;
				}
				else
				{
					cout << "Uncorrect input! Please, try again." << endl;
					cout << "The time must be more than " << first << " and less than " << last << endl;
				}
			} while (t != last);
		}

		system("cls");

		cout << "Enter the departure times of the transport from the last station on weekdays:" << endl;
		cout << "Enter the time of the first time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;
		first = InTime(24);
		T.wtime2.push_back(first);
		cout << "\nEnter the time of the last time departure: ";
		cout << "\n(The input format must be like: hh.mm)" << endl;

		last = InTime(24);

		while (last < first)
		{
			cout << "This time must be more than" << first << endl;
			cout << "Please, try again: ";
			last = InTime(24);
		}

		flag = 0;
		cout << "\n1.Enter the interval";
		cout << "\n2.Enter the other times";
		do {
			switch (_getch())
			{
			case '1':
				flag = 1;
				break;
			case'2':
				flag = 2;
				break;
			}
		} while (!flag);

		if (flag == 1)
		{
			cout << "\n\nEnter the interval of departure: ";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			t = InTime(12);
			while ((first + t) < last)
			{
				first += t;
				T.wtime2.push_back(first);
			}
			T.wtime2.push_back(last);
		}
		else
		{
			cout << "\nEnter the other times(the last time - the end of the entering):";
			cout << "\n(The input format must be like: hh.mm)" << endl;
			do {

				t = InTime(24);
				if (t > first && t <= last)
				{
					T.wtime2.push_back(t);
					first = t;
				}
				else
				{
					cout << "Uncorrect choise! Please, try again." << endl;
					cout << "The time must be more than " << first << " and less than " << last << endl;
				}
			} while (t != last);
		}
	}

	return stream;
}
ostream& operator<<(ostream& stream, Ground_Trans& T)
{
	stream << "||" << setw(4) << T.getnumber() << '.' << T.stops[0]->getname() << " - " << T.stops[T.stops.getsize() - 1]->getname();
	stream << setw(38 - T.stops[0]->getname().size() - T.stops[T.stops.getsize() - 1]->getname().size()) << "||" << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Ground_Trans& T)
{
	int size;
	stream << dynamic_cast<Transport&> (T);
	size = T.time1.size();
	stream << endl << setw(5) << size;
	for (int i = 0; i < size; i++)
		stream << T.time1[i];
	size = T.time2.size();
	stream << endl << setw(5) << size;
	for (int i = 0; i < size; i++)
		stream << T.time2[i];
	size = T.wtime1.size();
	stream << endl << setw(5) << size;
	for (int i = 0; i < size; i++)
		stream << T.wtime1[i];
	size = T.wtime2.size();
	stream << endl << setw(5) << size;
	for (int i = 0; i < size; i++)
		stream << T.wtime2[i];
	return stream;
}
ifstream& operator>>(ifstream& stream, Ground_Trans& T)
{
	int size;
	stream >> dynamic_cast<Transport&> (T);
	stream >> size;
	T.time1.resize(size);
	for (int i = 0; i < size; i++)
		stream >> T.time1[i];
	stream >> size;
	T.time2.resize(size);
	for (int i = 0; i < size; i++)
		stream >> T.time2[i];
	stream >> size;
	T.wtime1.resize(size);
	for (int i = 0; i < size; i++)
		stream >> T.wtime1[i];
	stream >> size;
	T.wtime2.resize(size);
	for (int i = 0; i < size; i++)
		stream >> T.wtime2[i];
	return stream;
}