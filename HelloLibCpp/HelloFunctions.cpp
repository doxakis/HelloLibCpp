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
			if (arr[i] == 0)
			{
				sum += arr[i];
			}
		}

		int* arr2;
		arr2 = new int[length];
		for (int i = 0; i < length; i++)
		{
			arr2[i] = i;
			sum += 1;
		}
		delete arr2;

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
			if (arr[i] == 0)
			{
				sum += arr[i];
			}
		}

		int* arr2 = (int*)malloc(length * sizeof(int));
		for (int i = 0; i < length; i++)
		{
			*(arr2 + i) = i;
			sum += 1;
		}
		free(arr2);

		return sum;
	}
}
