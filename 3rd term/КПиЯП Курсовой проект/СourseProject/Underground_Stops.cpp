#include "Underground_Stops.h"

void Underground_Stops::setline(int l)
{
	line = l;
}
void Underground_Stops::setnstops(Ring<Underground_Stops>& us)
{
	int id1, id2, j, f, k;
	vector<Nearest_St> stations;
	Nearest_St st;

	cout << "Enter the information about the near station: " << endl;

		id1 = 0;
		id2 = 0;
		for (j = 0;j < us.getsize() - 1;j++)
			if (us[j].getline() == line && us[j].getnstops().size() <= 1)
			{
				id1 = us[j].getid();
				j++;
				break;
			}
		for (j;j < us.getsize() - 1;j++)
			if (us[j].getline() == line && us[j].getnstops().size() <= 1)
			{
				id2 = us[j].getid();
				break;
			}
		if (id2 == 0) id2 = id1;
		cout << "ID(" << id1 << " or " << id2 << "): ";
		do {
			f = 0;
			st.id = InInt(1, us[us.getsize() - 2].getid());
			for (k = 0; k < us.getsize();k++)
				if ((st.id == us[k].getid()) & (st.id == id1 || st.id == id2))
				{
					f++;
					break;
				}
			if (!f) cout << "There are no stops with the same id or this\nstop doesen`t suit, please try again: ";
		} while (!f);
		cout << "Time to get to: ";
		cin >> st.time;
		stations.push_back(st);
		nearest = stations;
		st.id = getid();
		us[k].pushnstops(st);
}
int Underground_Stops::getline()
{
	return line;
}

Underground_Stops& Underground_Stops::operator=(Underground_Stops& st)
{
	Info = st.Info;
	line = st.line;
	nearest = st.nearest;

	return *this;
}

istream& operator>>(istream& stream, Underground_Stops& S)
{
	stream >> dynamic_cast<Stops&> (S);

	return stream;
}
ostream& operator<<(ostream& stream, Underground_Stops& S)
{
	stream << "||" << setw(4) << S.getid() << '.' << S.getname() << setw(41 - S.getname().size()) << "||" << endl;

	return stream;
}
ofstream& operator<<(ofstream& stream, Underground_Stops& S)
{
	stream << dynamic_cast<Stops&> (S);
	stream << setw(5) << S.line;
	stream << setw(5) << S.nearest.size();
	for (int i = 0; i < S.nearest.size(); i++)
	{
		stream << setw(5);
		stream << S.nearest[i];
	}
	return stream;
}
ifstream& operator>>(ifstream& stream, Underground_Stops& S)
{
	int size;
	stream >> dynamic_cast<Stops&> (S);
	stream >> S.line;
	stream >> size;
	S.nearest.resize(size);
	for (int i = 0; i < size; i++)
		stream >> S.nearest[i];
	return stream;
}