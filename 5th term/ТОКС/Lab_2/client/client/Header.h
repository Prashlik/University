#pragma once
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

const string flag = "01111110";
const string stuffed = "011111110";

string read(HANDLE);
bool write(HANDLE, string);
DWORD setBaudrate();

string encode(string buffer);
string decode(string buffer);
vector<string> packData(string buffer);
string unpackData(string packedData);
