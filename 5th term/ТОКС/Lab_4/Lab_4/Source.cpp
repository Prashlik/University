#include "CSMA.h"

int main() {
	CSMA st1("Station_1", 111);
	CSMA st2("Station_2", 222);
	CSMA st3("Station_3", 666);

	st1.start();
	st2.start();
	st3.start();
	
	cin.get();

	st1.stop();
	st2.stop();
	st3.stop();
}