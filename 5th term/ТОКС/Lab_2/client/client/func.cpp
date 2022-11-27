#include "Header.h"

#define PACKET_SIZE 64

string read(HANDLE hFile)
{
	char buf[49] = "";
	string msg, strbuf;
	unsigned long state = 0;

	if (SetCommMask(hFile, EV_RXCHAR)) {

		DWORD bytesReaded;
		do
		{
			if (!ReadFile(hFile, &buf, 11, &bytesReaded, NULL))
				cout << GetLastError() << endl;
			strbuf = encode(buf);
			strbuf = unpackData(strbuf);
			cout << "Unpacked message: " << strbuf << endl;
			strbuf = decode(strbuf);
			cout << "Decoded message: " << strbuf << endl;
			msg += strbuf;
			if (strbuf.find("\n") != -1) break;
			strbuf = "";
		} while (1);

		return msg;
	}
}


bool write(HANDLE hFile, string buffer)
{
	vector<string> packs;
	int i = 0;
	string encodedMsg = encode(buffer);
	cout << "Encoded message: " << encodedMsg << endl;
	packs = packData(encodedMsg);
	for (auto pack : packs)
	{
		cout << "Packed message: " << pack.c_str() << endl;
		WriteFile(hFile, pack.c_str(), pack.size(), NULL, NULL);
	}

	if (!strcmp(buffer.c_str(), "exit\n"))
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

string encode(string buffer) {

	string encodedData;
	int i = 0;
	while (i < buffer.size())
		encodedData += bitset<8>(buffer[i++]).to_string();

	return encodedData;
}

string decode(string buffer) {
	string decodedData;
	for (int i = 0; i < buffer.size() / 8; i++)
	{
		decodedData += strtol(buffer.substr(i * 8, 8).c_str(), NULL, 2);
	}
	return decodedData;
}

vector<string> packData(string buffer) {
	vector<string> packs;
	for (int i = 0; i <= buffer.size() / PACKET_SIZE; i++)
	{
		packs.push_back("");
		string packedMsg(buffer.substr(i * PACKET_SIZE, PACKET_SIZE));
		int poz = 0;
		while (1)
		{
			poz = packedMsg.find("111111", poz);
			if (poz != -1)
			{
				packedMsg.insert(poz, "1");
				poz += 6;
			}
			else break;
		}
		while (packedMsg.size() != PACKET_SIZE + 8) packedMsg.push_back('0');
		int ones = 0;
		for (auto digit : packedMsg) if (digit == '1') ones++;
		packedMsg.insert(0, flag);
		packs[i] = decode(packedMsg);
		packs[i].insert(1, to_string(ones % 2));
	}
	return packs;
}

string unpackData(string packedData) {

	int parityBit = (int)decode(packedData.substr(8, 8))[0] - 48;
	packedData.erase(8, 8);
	int poz = packedData.find(flag);
	if (poz == -1) return "";
	else packedData.erase(0, 8);
	int ones = 0;
	for (auto digit : packedData) if (digit == '1') ones++;
	if (ones % 2 != parityBit) return "";
	poz = 0;
	while (1)
	{
		poz = packedData.find("1111111", poz);
		if (poz != -1)
		{
			packedData.erase(poz, 1);
			packedData.push_back('0');
			poz += 6;
		}
		else break;
	}
	return packedData;
}