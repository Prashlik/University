#pragma once
#include <thread>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <conio.h>

using namespace std;

#define JAM_SIGNAL 0xFFFFFFFF
#define MAX_TRIES 5
#define COLISION_DELAY 10

class CSMA {
private:
	thread* thrd;
	string name;
	static unsigned trans_msg;
	bool running;
	int delay;

	static void transmit(CSMA* station);
	static void generateMsg(unsigned& msg);
	static void changeClr(int color);

public:

	CSMA(string name, int delay);
	void start();
	void stop();
};
