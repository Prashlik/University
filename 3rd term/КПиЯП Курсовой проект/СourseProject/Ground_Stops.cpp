#include "Ground_Stops.h"

void Ground_Stops::settrans(int flag, Ring<Ground_Trans*> trans)
{
	switch (flag)
	{
	case 1:
		buses = trans;
		break;
	case 2:
		trolleybuses = trans;
		break;
	case 3:
		trams = trans;
		break;
	}
}
void Ground_Stops::pushtrans(int flag, Ground_Trans* trans)
{
	switch (flag)
	{
	case 1:
		buses.push(trans);
		break;
	case 2:
		trolleybuses.push(trans);
		break;
	case 3:
		trams.push(trans);
		break;
	}
}
void Ground_Stops::setnstops(Ring<Ground_Stops> &gs)
{
	int num, i, k;
	vector<Nearest_St> stations;
	Nearest_St st;

	system("cls");

	cout << "Enter the amount of the nearest ground stations:\n";

	if (gs.getsize() > 4)
		num = InInt(1, 4);
	else num = InInt(1, getid() - 1);

	for (i = 0;i < num;i++)
	{
		int f;
		cout << i + 1 << ")ID(from " << 1 << " to " << gs.getsize() - 1 << "): ";
		do {
			f = 0;
			st.id = InInt(1, gs.getsize() - 1);
			for (int j = 0; j < stations.size();j++)
				if (st.id == stations[j].id || st.id == getid())
				{
					f = -1;
					cout << "This station is allready included, please, try again: ";
				}
			if (f == 0)
				for (k = 0; k < gs.getsize();k++)
					if (st.id == gs[k].getid())
					{
						f = 1;
						break;
					}
			if (!f) cout << "There are no stops with the same id, please try again: ";
		} while (f <= 0);
		cout << "Time to get to: ";
		cin >> st.time;
		stations.push_back(st);
		st.id = getid();
		gs[k].pushnstops(st);
	}

	nearest = stations;
}

Ring<Ground_Trans*> Ground_Stops::gettrans(int flag)
{
	switch (flag)
	{
	case 1:
		return buses;
	case 2:
		return trolleybuses;
	case 3:
		return trams;
	}
	return 0;
}

void Ground_Stops::info()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	int hflag = 1;

	if (buses.getsize() != 0)
		buses.sort();
	if (trolleybuses.getsize() != 0)
		trolleybuses.sort();
	if (trams.getsize() != 0)
		trams.sort();
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "============== " << getname() << setw(33 - getname().size()) << " ================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter'- to choose the number of the route)||" << endl;
			if (hflag == 1)
			{
				cout << "||---[1.Buses]-- 2.Trolleybuses -- 3.Trams ---||" << endl;
				for (int i = 0; i < buses.getsize();i++)
					cout << *buses[i];
				if (!buses.getsize())
					cout << "||    The list is empty!                      ||" << endl;
			}
			else if (hflag == 2)
			{
				cout << "||--- 1.Buses --[2.Trolleybuses]-- 3.Trams ---||" << endl;
				for (int i = 0; i < trolleybuses.getsize();i++)
					cout << *trolleybuses[i];
				if (!trolleybuses.getsize())
					cout << "||    The list is empty!                      ||" << endl;
			}
			else if (hflag == 3)
			{
				cout << "||--- 1.Buses -- 2.Trolleybuses --[3.Trams]---||" << endl;
				for (int i = 0; i < trams.getsize();i++)
					cout << *trams[i];
				if (!trams.getsize())
					cout << "||    The list is empty!                      ||" << endl;
			}
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::LEFT:
						if (hflag == 1)
							hflag = 3;
						else hflag--;
						key++;
						break;
					case Keys::RIGHT:
						if (hflag == 3)
							hflag = 1;
						else hflag++;
						key++;
						break;
					case Keys::ESC:
						vflag = 0;
						flag++;
						key++;
						break;
					case Keys::ENTER:
						flag++;
						key++;
						break;
					}
				}
			} while (!key);
		} while (!flag);

		if (vflag)
		{
			int flag = 0;
			switch (hflag)
			{
			case 1:
			{
				if (buses.getsize() != 0)
				{
					Time t;
					int numb, i;
					cout << "Enter the number of the route: ";
					do
					{
						numb = InInt(1, 100);

						for (i = 0; i < buses.getsize() && buses[i]->getnumber() != numb;i++);
						if (buses[i]->getnumber() == numb)
						{
							numb = i;
							flag++;
						}
						else
							cout << "There are no transport with this number.\nPlease, try again: ";
					} while (!flag);
					buses[numb]->stopinfo(getid());
				}
				else
				{
					cout << "There are no objects with the type 'bus'!" << endl;
					system("pause");
				}
				break;
			}
			case 2:
			{
				if (trolleybuses.getsize() != 0)
				{
					int numb, i;
					cout << "Enter the number of the route: ";
					do
					{
						numb = InInt(1, trolleybuses[trolleybuses.getsize()]->getnumber());

						for (i = 0; i < trolleybuses.getsize() && trolleybuses[i]->getnumber() != numb;i++);
						if (trolleybuses[i]->getnumber() == numb)
						{
							numb = i;
							flag++;
						}
						else
							cout << "There are no transport with this number.\nPlease, try again: ";
					} while (!flag);
					trolleybuses[numb]->stopinfo(getid());
				}
				else
				{
					cout << "There are no objects with the type 'trolleybus'!" << endl;
					system("pause");
				}
				break;
			}
			case 3:
			{
				if (trams.getsize() != 0)
				{
					int numb, i;
					cout << "Enter the number of the route: ";
					do
					{
						numb = InInt(1, trams[trams.getsize()]->getnumber());

						for (i = 0; i < trams.getsize() && trams[i]->getnumber() != numb;i++);
						if (trams[i]->getnumber() == numb)
						{
							numb = i;
							flag++;
						}
						else
							cout << "There are no transport with this number.\nPlease, try again: ";
					} while (!flag);
					trams[numb]->stopinfo(getid());
				}
				else
				{
					cout << "There are no objects with the type 'tram'!" << endl;
					system("pause");
				}
				break;
			}
			}

		}


	} while (vflag);
}

Ground_Stops& Ground_Stops::operator=(Ground_Stops& st)
{
	Info = st.Info;
	buses = st.buses;
	trams = st.trams;
	trolleybuses = st.trolleybuses;
	nearest = st.nearest;
	return *this;
}

istream& operator>>(istream& stream, Ground_Stops& S)
{
	stream >> dynamic_cast<Stops&> (S);

	return stream;
}
ostream& operator<<(ostream& stream, Ground_Stops& S)
{
	stream << "||" << setw(3) << S.getid() << ". " << S.getname() << setw(41 - S.getname().size()) << "||" << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Ground_Stops& S)
{
	stream << dynamic_cast<Stops&> (S);
	stream << setw(5) << S.nearest.size();
	for (int i = 0; i < S.nearest.size(); i++)
	{
		stream << setw(5);
		stream << S.nearest[i];
	}
	return stream;
}
ifstream& operator>>(ifstream& stream, Ground_Stops& S)
{
	int size;
	stream >> dynamic_cast<Stops&> (S);
	stream >> size;
	S.nearest.resize(size);
	for (int i = 0; i < size; i++)
		stream >> S.nearest[i];
	return stream;
}