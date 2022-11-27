#include "CSMA.h"

#define blue 0x09
#define green 0x0A
#define red 0x0C
#define white 0x0F

unsigned CSMA::trans_msg = 0;

CSMA::CSMA(string name, int delay) {
	this->name = name;
	this->delay = delay;
	this->running = false;
};

void CSMA::start() {
	thrd = new thread(transmit, this);
	running = true;
};

void CSMA::stop() {
	running = false;
	thrd->join();

	changeClr(blue);
	cout << name << "stopped." << endl;
	changeClr(white);
};


void CSMA::changeClr(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | color));
};

void CSMA::generateMsg(unsigned& msg) {
	srand(clock() + GetCurrentThreadId());
	msg = rand() << 16;
	msg |= rand();
};


void CSMA::transmit(CSMA* station) {

	while (station->running) {
		Sleep(station->delay);
		unsigned msg;
		generateMsg(msg);
		int try_counter = 0;
		while (true) {
			if (!try_counter && CSMA::trans_msg == JAM_SIGNAL)
				break;

			CSMA::trans_msg |= msg;
			Sleep(COLISION_DELAY);

			if (CSMA::trans_msg == msg) {
				changeClr(green);
				cout << "Success transmition from " << station->name << ": 0x" << setfill('0') << setw(8) << std::hex << std::uppercase << trans_msg << endl;
				CSMA::trans_msg = 0;
				break;
			}
			else {
				CSMA::trans_msg = JAM_SIGNAL;
				changeClr(red);
				try_counter++;
				cout << "Collision detected from " << station->name << ", try to resolve: " << try_counter << endl;
				cout << "Transmitting JAM SIGNAL from " << station->name << endl;
				if (try_counter == MAX_TRIES) {
					cout << "Unable to resolve, skipping" << endl;
					break;
				}

				int time_slot = rand() % ((int)pow(2, try_counter) + 1);
				Sleep(time_slot * 100);                                                       
				CSMA::trans_msg = 0;
			}
		}
	}
};