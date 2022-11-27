#pragma once
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <bitset>
#include <string>

using namespace std;

string read(HANDLE);
bool write(HANDLE, string);
DWORD setBaudrate();