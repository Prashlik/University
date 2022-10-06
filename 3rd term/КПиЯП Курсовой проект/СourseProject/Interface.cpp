#include "Interface.h"

void Interface::open()
{
	gid.clear();
	uid.clear();
	us.Delete();
	gs.Delete();
	train.Delete();
	bus.Delete();
	trolleybus.Delete();
	tram.Delete();

	Text_File<StopsInfo> GrId("Data\\GrId.txt");
	Text_File<StopsInfo> UndId("Data\\UndId.txt");
	Text_File<Underground_Stops> UndStops("Data\\UndStops.txt");
	Text_File<Ground_Stops> GrStops("Data\\GrStops.txt");
	Text_File<Ground_Trans> Buses("Data\\Buses.txt");
	Text_File<Ground_Trans> Trolleybuses("Data\\Trolleybuses.txt");
	Text_File<Ground_Trans> Trams("Data\\Trams.txt");
	Text_File<Underground_Trans> Trains("Data\\Trains.txt");

	GrId.Open_in();
	if (!GrId.IsEmpty())
	{
		GrId.Remote();
		for (int i = 0;!GrId.End(); i++)
		{
			StopsInfo temp;
			GrId.Read(temp);
			gid.push_back(temp);
		}
	}

	UndId.Open_in();
	if (!UndId.IsEmpty())
	{
		UndId.Remote();
		for (int i = 0;!UndId.End(); i++)
		{
			StopsInfo temp;
			UndId.Read(temp);
			uid.push_back(temp);
		}
	}

	UndStops.Open_in();
	if (!UndStops.IsEmpty())
	{
		UndStops.Remote();
		for (int i = 0;!UndStops.End(); i++)
		{
			int l;
			Underground_Stops temp;
			UndStops.Read(temp);
			for (l = 0;temp.getid() != uid[l].id;l++);
			temp.setname(uid[l].name);
			us.push(temp);

		}
	}

	GrStops.Open_in();
	if (!GrStops.IsEmpty())
	{
		GrStops.Remote();
		for (int i = 0;!GrStops.End(); i++)
		{
			int l;
			Ground_Stops temp;
			GrStops.Read(temp);
			for (l = 0;temp.getid() != gid[l].id;l++);
			temp.setname(gid[l].name);
			gs.push(temp);
		}
	}

	Buses.Open_in();
	if (!Buses.IsEmpty())
	{
		Buses.Remote();
		for (int i = 0;!Buses.End();i++)
		{
			int size = 0;
			vector<int> st;
			Ground_Trans temp;
			Buses.Read(temp);
			size = (int)temp.getst().size();
			st = temp.getst();
			bus.push(temp);
			for (int l = 0;l < size;l++)
			{
				int k;
				for (k = 0;st[l] != gs[k].getid();k++);
				bus[bus.getsize() - 1].pushstops(&gs[k]);
				gs[k].pushtrans(1, &bus[bus.getsize() - 1]);
			}
		}
	}

	Trolleybuses.Open_in();
	if (!Trolleybuses.IsEmpty())
	{
		Trolleybuses.Remote();
		for (int i = 0;!Trolleybuses.End();i++)
		{
			int size = 0;
			vector<int> st;
			Ground_Trans temp;
			Trolleybuses.Read(temp);
			size = (int)temp.getst().size();
			st = temp.getst();
			trolleybus.push(temp);
			for (int l = 0;l < size;l++)
			{
				int k;
				for (k = 0;st[l] != gs[k].getid();k++);
				trolleybus[trolleybus.getsize() - 1].pushstops(&gs[k]);
				gs[k].pushtrans(2, &trolleybus[bus.getsize() - 1]);
			}
		}
	}

	Trams.Open_in();
	if (!Trams.IsEmpty())
	{
		Trams.Remote();
		for (int i = 0;!Trams.End();i++)
		{
			int size = 0;
			vector<int> st;
			Ground_Trans temp;
			Trams.Read(temp);
			size = (int)temp.getst().size();
			st = temp.getst();
			tram.push(temp);
			for (int l = 0;l < size;l++)
			{
				int k;
				for (k = 0;st[l] != gs[k].getid();k++);
				tram[tram.getsize() - 1].pushstops(&gs[k]);
				gs[k].pushtrans(3, &tram[bus.getsize() - 1]);
			}
		}
	}

	Trains.Open_in();
	if (!Trains.IsEmpty())
	{
		Trains.Remote();
		for (int i = 0;!Trains.End(); i++)
		{
			int k;
			int size = 0;
			vector<Underground_Stops*> stations;
			vector<int> st;
			Underground_Trans temp;
			Trains.Read(temp);
			size = (int)temp.getst().size();
			st = temp.getst();
			for (int l = 0;l < size;l++)
			{
				for (k = 0;st[l] != us[k].getid();k++);
				stations.push_back(&us[k]);
				us[k].setline(temp.getnumber());
			}

			temp.setstops(stations);
			train.push(temp);
		}
	}
}

void Interface::save()
{
	Text_File<StopsInfo> GrId("Data\\GrId.txt");
	GrId.Open_out();
	for (int i = 0;i < gid.size();i++)
		GrId.Write(gid[i]);
	Text_File<StopsInfo> UndId("Data\\UndId.txt");
	UndId.Open_out();
	for (int i = 0;i < uid.size();i++)
		UndId.Write(uid[i]);
	Text_File<Underground_Stops> UndStops("Data\\UndStops.txt");
	UndStops.Open_out();
	for (int i = 0;i < us.getsize();i++)
		UndStops.Write(us[i]);
	Text_File<Ground_Stops> GrStops("Data\\GrStops.txt");
	GrStops.Open_out();
	for (int i = 0;i < gs.getsize();i++)
		GrStops.Write(gs[i]);
	Text_File<Ground_Trans> Buses("Data\\Buses.txt");
	Buses.Open_out();
	for (int i = 0;i < bus.getsize();i++)
		Buses.Write(bus[i]);
	Text_File<Ground_Trans> Trolleybuses("Data\\Trolleybuses.txt");
	Trolleybuses.Open_out();
	for (int i = 0;i < trolleybus.getsize();i++)
		Trolleybuses.Write(trolleybus[i]);
	Text_File<Ground_Trans> Trams("Data\\Trams.txt");
	Trams.Open_out();
	for (int i = 0;i < tram.getsize();i++)
		Trams.Write(tram[i]);
	Text_File<Underground_Trans> Trains("Data\\Trains.txt");
	Trains.Open_out();
	for (int i = 0;i < train.getsize();i++)
		Trains.Write(train[i]);
}

void Interface::Choose()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "==================== MENU ======================" << endl;
			cout << "||=======(Press Esc to end the program)=======||" << endl;
			if (vflag == 1)
				cout << "||---------[1. Show all the stations]---------||" << endl;
			else
				cout << "||--------- 1. Show all the stations ---------||" << endl;
			if (vflag == 2)
				cout << "||----------[2. Show all transport]-----------||" << endl;
			else
				cout << "||---------- 2. Show all transport -----------||" << endl;
			if (vflag == 3)
				cout << "||-----------[3. Do some changes]-------------||" << endl;
			else
				cout << "||----------- 3. Do some changes -------------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 3;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 3)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
			Stops();
			flag = 0;
			break;
		case 2:
			cout << vflag;
			Trans();
			break;
		case 3:
			cout << vflag;
			Change();
			break;
		}
	} while (vflag);
}

void Interface::Change()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== CHANGES =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||------------[1. Add an element]-------------||" << endl;
			else
				cout << "||------------ 1. Add an element -------------||" << endl;
			if (vflag == 2)
				cout << "||-------[2. Change some information]---------||" << endl;
			else
				cout << "||------- 2. Change some information ---------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 2;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 2)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
			Add();
			break;
		case 2:
			ChangeSmth();
			break;
		}

		if (!vflag)
		{
			flag = 0;
			do
			{
				cout << "Are you sure to save the changes?" << endl << endl;
				cout << "0)Turn back." << endl;
				cout << "1)Yes." << endl;
				cout << "2)No." << endl;
				switch (_getch())
				{
				case '1':
					save();
					flag++;
					break;
				case '2':
					open();
					flag++;
					break;
				case '0':
					vflag = 1;
					flag++;
					break;
				}
			} while (!flag);
		}

	} while (vflag);
}

void Interface::Add()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== CHANGES =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||---------[1. Add a ground station]----------||" << endl;
			else
				cout << "||--------- 1. Add a ground station ----------||" << endl;
			if (vflag == 2)
				cout << "||------[2. Add an underground station]-------||" << endl;
			else
				cout << "||------ 2. Add an underground station -------||" << endl;
			if (vflag == 3)
				cout << "||----------[3. Add a ground route]-----------||" << endl;
			else
				cout << "||---------- 3. Add a ground route -----------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 3;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 3)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
		{
			int numb = gs.getsize() + 1;
			Ground_Stops temp;

			temp.setid(numb);
			gs.push(temp);

			StopsInfo info;
			info.id = temp.getid();
			gid.push_back(info);

			InName(gid, gs[gs.getsize() - 1]);

			if (gs.getsize() > 1)
				gs[gs.getsize() - 1].setnstops(gs);
			break;
		}
		case 2:
		{
			Underground_Stops temp;
			int i, f = 0;
			vector<Nearest_St> stations;
			Nearest_St st;

			cout << "Enter the number of the branch: ";
			int numb = InInt(1, train.getsize() + 1);

			temp.setline(numb);

			i = us.getsize() + 1;
			temp.setid(i);

			us.push(temp);

			StopsInfo info;
			info.id = temp.getid();
			uid.push_back(info);

			InName(uid, us[us.getsize() - 1]);

			for (i = 0;i < us.getsize(); i++)
				if (us[i].getline() == temp.getline())
					f++;
			if (f > 1)
				us[us.getsize() - 1].setnstops(us);

			if (numb > train.getsize())
			{
				Underground_Trans ttemp;
				ttemp.setnumber(numb);
				cin >> ttemp;
				ttemp.pushst(temp.getid());
				ttemp.pushstops(&us[us.getsize() - 1]);
				train.push(ttemp);
			}
			else
			{
				train[temp.getline() - 1].pushst(temp.getid());
				train[temp.getline() - 1].pushstops(&us[us.getsize() - 1]);
			}
			break;
		}
		case 3:
		{
			Ground_Trans temp;
			int numb;

			do
			{
				flag = 0;
				cout << "Choose the type of the transport:" << endl;
				cout << "1.Bus\n2.Trolleybus\n3.Tram\n";

				switch (_getch())
				{
				case '1':
					cin >> temp;
					for (numb = 0;numb < bus.getsize();numb++)
						if (bus[numb].getnumber() != numb + 1)
							break;
					numb++;
					temp.setnumber(numb);
					bus.push(temp);
					bus[bus.getsize() - 1].setstops(gs, 1);
					bus.sort();
					flag++;
					break;
				case '2':
					cin >> temp;
					for (numb = 0;numb < trolleybus.getsize();numb++)
						if (trolleybus[numb].getnumber() != numb + 1)
							break;
					numb++;
					temp.setnumber(numb);
					trolleybus.push(temp);
					trolleybus[trolleybus.getsize() - 1].setstops(gs, 2);
					trolleybus.sort();
					flag++;
					break;
				case '3':
					cin >> temp;
					for (numb = 0;numb < tram.getsize();numb++)
						if (tram[numb].getnumber() != numb + 1)
							break;
					numb++;
					temp.setnumber(numb);
					tram.push(temp);
					tram[tram.getsize() - 1].setstops(gs, 3);
					tram.sort();
					flag++;
					break;
				}
			} while (!flag);
		}
		}
	} while (vflag);
}

void Interface::ChangeSmth()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== CHANGES =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||---[1. Change information about stations]---||" << endl;
			else
				cout << "||--- 1. Change information about stations ---||" << endl;
			if (vflag == 2)
				cout << "||--[2. Change information about transport]---||" << endl;
			else
				cout << "||-- 2. Change information about transport ---||" << endl;
			if (vflag == 3)
				cout << "||--------------[3. Delete all]---------------||" << endl;
			else
				cout << "||-------------- 3. Delete all ---------------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 3;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 3)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
			ChangeStops();
			break;
		case 2:
			ChangeTrans();
			break;
		case 3:
			gid.clear();
			uid.clear();
			us.Delete();
			gs.Delete();
			train.Delete();
			bus.Delete();
			trolleybus.Delete();
			tram.Delete();
			cout << "Deleted!" << endl;
			system("pause");
			break;
		}

	} while (vflag);
}

void Interface::ChangeStops()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== CHANGES =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||--[1. Change the name of ground station]----||" << endl;
			else
				cout << "||-- 1. Change the name of ground station ----||" << endl;
			if (vflag == 2)
				cout << "||[2. Change the name of underground station]-||" << endl;
			else
				cout << "|| 2. Change the name of underground station -||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 2;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 2)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
		{
			int f = 0, numb, num = 0;
			string name;
			numb = SearchStop(gs);
			if (numb != -1)
			{
				cout << "Enter the new name: \n";
				InName(gid, gs[numb]);
			}
			break;
		}
		case 2:
		{
			int f = 0, numb, num = 0;
			string name;
			numb = SearchStop(us);
			if (numb != -1)
			{
				cout << "Enter the new name: \n";
				InName(uid, us[numb]);
			}
			break;
		}
		}

	} while (vflag);
}

void Interface::ChangeTrans()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== CHANGES =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||----------[1. Change ground route]----------||" << endl;
			else
				cout << "||---------- 1. Change ground route ----------||" << endl;
			if (vflag == 2)
				cout << "||--------[2. Change ground timetable]--------||" << endl;
			else
				cout << "||-------- 2. Change ground timetable --------||" << endl;
			if (vflag == 3)
				cout << "||--------[3. Delete the ground route]--------||" << endl;
			else
				cout << "||-------- 3. Delete the ground route --------||" << endl;
			if (vflag == 4)
				cout << "||------[4. Change underground interval]------||" << endl;
			else
				cout << "||------ 4. Change underground interval ------||" << endl;
			if (vflag == 5)
				cout << "||-----[5. Delete the underground route]------||" << endl;
			else
				cout << "||----- 5. Delete the underground route ------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 5;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 5)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
		{
			int f = 0, numb;
			do {
				cout << "1.Bus" << endl;
				cout << "2.Trolleybus" << endl;
				cout << "3.Tram" << endl;
				switch (_getch())
				{
				case '1':
					if (numb = SearchGTrans(bus) > -1)
						bus[numb].setstops(gs, 1);
					f++;
					break;
				case '2':
					if (numb = SearchGTrans(trolleybus) > -1)
						trolleybus[numb].setstops(gs, 2);
					f++;
					break;
				case '3':
					if (numb = SearchGTrans(tram) > -1)
						tram[numb].setstops(gs, 3);
					f++;
					break;
				}
			} while (!f);
			break;
		}
		case 2:
		{
			int f = 0, numb;
			do {
				cout << "1.Bus" << endl;
				cout << "2.Trolleybus" << endl;
				cout << "3.Tram" << endl;
				switch (_getch())
				{
				case '1':
					if (numb = SearchGTrans(bus) > -1)
						cin >> bus[numb];
					f++;
					break;
				case '2':
					if (numb = SearchGTrans(trolleybus) > -1)
						cin >> trolleybus[numb];
					f++;
					break;
				case '3':
					if (numb = SearchGTrans(tram) > -1)
						cin >> tram[numb];
					f++;
					break;
				}
			} while (!f);
			break;
		}
		case 3:
		{
			int f = 0, numb;
			do {
				cout << "1.Bus" << endl;
				cout << "2.Trolleybus" << endl;
				cout << "3.Tram" << endl;
				switch (_getch())
				{
				case '1':
					if (numb = SearchGTrans(bus) > -1)
						bus[numb].delstops(1);
					bus.DeleteNode(numb);
					f++;
					break;
				case '2':
					if (numb = SearchGTrans(trolleybus) > -1)
						trolleybus[numb].delstops(2);
					trolleybus.DeleteNode(numb);
					f++;
					break;
				case '3':
					if (numb = SearchGTrans(tram) > -1)
						tram[numb].delstops(3);
					tram.DeleteNode(numb);
					f++;
					break;
				}
			} while (!f);
			break;
		}
		case 4:
		{
			int numb;
			if (!train.getsize())
			{
				cout << "There are no trains!" << endl;
				system("pause");
				break;
			}
			cout << "Enter the number of the route: ";
			numb = InInt(1, train.getsize());
			cin >> train[numb - 1];
			break;
		}
		case 5:
		{
			int numb, i;
			if (!train.getsize())
			{
				cout << "There are no trains!" << endl;
				system("pause");
				break;
			}
			cout << "Enter the number of the line: ";
			numb = InInt(1, train.getsize());
			for (i = 0;i < us.getsize();i++)
				if (us[i].getline() == numb)
				{
					us.DeleteNode(i);
					i--;
				}
			train.DeleteNode(numb);
			while (numb <= train.getsize())
			{
				train[numb].setnumber(numb);
				for (i = 0;i < us.getsize();i++)
					if (us[i].getid() == numb + 1)
						us[i].setline(numb);
				numb++;
			}
			break;
		}
		}
		if (vflag)
		{
			cout << "Success!\n";
			system("pause");
		}
	} while (vflag);
}

void Interface::Stops()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "==================== STOPS =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			if (vflag == 1)
				cout << "||-------------[1. Ground stops]--------------||" << endl;
			else
				cout << "||------------- 1. Ground stops --------------||" << endl;
			if (vflag == 2)
				cout << "||-----------[2. Underground stops]-----------||" << endl;
			else
				cout << "||----------- 2. Underground stops -----------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 2;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 2)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
			GrStops();
			flag = 0;
			break;
		case 2:
			cout << vflag;
			UndStops();
			break;
		}
	} while (vflag);
}

void Interface::GrStops()
{
	bool flag = 0, key = 0;
	int vflag = 1;

	if (gs.getsize() != 0)
		gs.sort();

	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================= GROUND STOPS =================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter' - to choose the number of the stop)||" << endl;
			for (int i = 0; i < gs.getsize(); i++)
				cout << "||" << setw(3) << i + 1 << ". " << gs[i].getname() << setw(41 - gs[i].getname().size()) << "||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
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
			if (gs.getsize() != 0)
			{
				cout << "Enter the number of the station: ";
				int numb = InInt(1, gs.getsize());
				gs[numb - 1].info();
			}
			else
			{
				cout << "There are no stops!" << endl;
				system("pause");
			}
		}
	} while (vflag);
}

void Interface::UndStops()
{
	bool flag = 0, key = 0;
	int vflag = 1;

	if (us.getsize() != 0)
		us.sort();

	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "============== UNDERGROUND STOPS ===============" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter' - to choose the number of the stop)||" << endl;
			for (int i = 0; i < us.getsize(); i++)
				cout << "||" << setw(3) << i + 1 << ". " << us[i].getname() << setw(41 - us[i].getname().size()) << "||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
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
			if (us.getsize() != 0)
			{
				cout << "Enter the number of the station: ";
				int numb = InInt(1, us.getsize());
				numb--;
				Time t = train[us[numb].getline()].getinterval();
				Time wt = train[us[numb].getline()].getwinterval();
				cout << "=========== STATION " << setw(15) << us[numb].getname() << " ============" << endl;
				cout << "||========(Press any key to turn back)========||" << endl;
				cout << "|| Line: " << setw(2) << us[numb].getline() << setw(37) << "||" << endl;
				cout << "|| Interval on weekdays: " << t << setw(19) << "||" << endl;
				cout << "|| Interval on weekends: " << wt << setw(19) << "||" << endl;
				cout << "||============================================||" << endl;
			}
			else cout << "There are no metro stations!" << endl;
			system("pause");
		}
	} while (vflag);
}

void Interface::Trans()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "================== TRANSPORT ===================" << endl;
			cout << "||=======(Press Esc to end the program)=======||" << endl;
			if (vflag == 1)
				cout << "||-----------[1. Ground transport]------------||" << endl;
			else
				cout << "||----------- 1. Ground transport ------------||" << endl;
			if (vflag == 2)
				cout << "||---------[2. Underground transport]---------||" << endl;
			else
				cout << "||--------- 2. Underground transport ---------||" << endl;
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
					case Keys::UP:
						if (vflag == 1)
							vflag = 2;
						else vflag--;
						key++;
						break;
					case Keys::DOWN:
						if (vflag == 2)
							vflag = 1;
						else vflag++;
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

		switch (vflag)
		{
		case 1:
			GrTrans();
			flag = 0;
			break;
		case 2:
			cout << vflag;
			UndTrans();
			break;
		}
	} while (vflag);
}

void Interface::GrTrans()
{
	bool flag = 0, key = 0;
	int vflag = 1;
	int hflag = 1;

	if (bus.getsize() != 0)
		bus.sort();
	if (trolleybus.getsize() != 0)
		trolleybus.sort();
	if (tram.getsize() != 0)
		tram.sort();
	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "============== GROUND TRANSPORT ================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter'- to choose the number of the route)||" << endl;
			if (hflag == 1)
			{
				cout << "||---[1.Buses]-- 2.Trolleybuses -- 3.Trams ---||" << endl;
				bus.PrintRing();
			}
			else if (hflag == 2)
			{
				cout << "||--- 1.Buses --[2.Trolleybuses]-- 3.Trams ---||" << endl;
				trolleybus.PrintRing();
			}
			else if (hflag == 3)
			{
				cout << "||--- 1.Buses -- 2.Trolleybuses --[3.Trams]---||" << endl;
				tram.PrintRing();
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
			int numb;
			switch (hflag)
			{
			case 1:
				numb = SearchGTrans(bus);
				if (numb != -1)
					bus[numb].info();
				break;
			case 2:
				numb = SearchGTrans(trolleybus);
				if (numb != -1)
					trolleybus[numb].info();
				break;
			case 3:
				numb = SearchGTrans(tram);
				if (numb != -1)
					tram[numb].info();
				break;
			}
		}
	} while (vflag);
}

void Interface::UndTrans()
{
	bool flag = 0, key = 0;
	int vflag = 1;

	if (train.getsize() != 0)
		train.sort();

	do {
		do {
			flag = 0;
			rewind(stdin);
			system("cls");
			cout << "==================== METRO =====================" << endl;
			cout << "||==========(Press Esc to turn back)==========||" << endl;
			cout << "||('Enter'- to choose the number of the route)||" << endl;
			train.PrintRing();
			cout << "||============================================||" << endl;

			do {
				key = 0;
				if (_kbhit())
				{
					switch (static_cast<Keys>(_getch()))
					{
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
			if (train.getsize() != 0)
			{
				cout << "Enter the number of the line: ";
				int numb = InInt(1, train.getsize());
				train[numb - 1].info();
			}
			else cout << "There are no objects with the type 'train'!" << endl;
			system("pause");
		}


	} while (vflag);
}