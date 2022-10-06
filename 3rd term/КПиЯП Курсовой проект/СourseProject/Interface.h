#pragma once
#include "Header.h"
#include <conio.h>

using namespace std;

class Interface
{
	vector<StopsInfo> gid, uid;
	Ring<Underground_Stops> us;
	Ring<Ground_Stops> gs;
	Ring<Underground_Trans> train;
	Ring<Ground_Trans> bus;
	Ring<Ground_Trans> trolleybus;
	Ring<Ground_Trans> tram;

public:

	Interface()
	{
		open();
	}

	~Interface() {}

	void open();
	void save();

	void Choose();

	void Change();
	void Add();

	void ChangeSmth();
	void ChangeStops();
	void ChangeTrans();

	void Stops();
	void GrStops();
	void UndStops();

	void Trans();
	void GrTrans();
	void UndTrans();
};
