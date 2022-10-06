#include "Header.h"


string read(HANDLE hFile)
{
	char buf = '\0';
	string msg;

	DWORD bytesReaded;
	do
	{
		if (!ReadFile(hFile, &buf, 1, &bytesReaded, NULL))
			cout << GetLastError() << endl;
		if (buf == '\n') break;
		msg += buf;
	} while (1);
	return msg;
}


bool write(HANDLE hFile, string buffer)
{
	int i = 0;
	cout << endl;
	while (i < buffer.size())
	{
		WriteFile(hFile, &(buffer[i++]), 1, NULL, NULL);
	}

	if (buffer == "exit\n")
		return false;
	else
		return true;

}

DWORD setBaudrate()
{
	DWORD baudRate;
	int flag;
	cout << "Select baudrate:" << endl << "1. 110" << endl << "2. 9600" << endl << "3. 14400" << endl << "4. 19200" << endl << "5. 38400" << endl << "6. 56000" << endl << "7. 256000" << endl;
	do {
		flag = 0;
		switch (_getch()) {

		case('1'):
			system("cls");
			baudRate = CBR_110;
			break;

		case('2'):
			system("cls");
			baudRate = CBR_9600;
			break;

		case('3'):
			system("cls");
			baudRate = CBR_14400;
			break;

		case('4'):
			system("cls");
			baudRate = CBR_19200;
			break;

		case('5'):
			system("cls");
			baudRate = CBR_38400;
			break;

		case('6'):
			system("cls");
			baudRate = CBR_56000;
			break;

		case('7'):
			system("cls");
			baudRate = CBR_256000;
			break;

		default:
			baudRate = CBR_19200;
			cout << endl << "Wrong input. Please try again:" << endl;
			flag = 1;
			break;

		}
	} while (flag);
	cout << "Baudrate " << baudRate << " is set." << endl << "Print 'exit' to end the program." << endl;
	return baudRate;
}