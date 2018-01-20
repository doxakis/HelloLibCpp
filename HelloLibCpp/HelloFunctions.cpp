#pragma once

#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

class HelloFunctions
{
public:
	static int parseFile(int* arr, int length)
	{
		int sum = 0;
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == 32)
			{
				sum += arr[i];
			}
		}
		return sum;
	}
};

// Define C functions for the C++ class - as ctypes can only talk to C...
extern "C"
{
	__declspec(dllexport) int __cdecl parseFileCpp(int* arr, int length)
	{
		//cout << "calling: parseFileCpp" << endl;
		//cout << "arr: " << arr << endl;
		//cout << "len: " << length << endl;
		return HelloFunctions::parseFile(arr, length);
	}

	__declspec(dllexport) int __cdecl parseFileC(int* arr, int length)
	{
		int sum = 0;
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == 32)
			{
				sum += arr[i];
			}
		}
		return sum;
	}
}
