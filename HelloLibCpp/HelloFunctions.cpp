#pragma once

#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include "cpplinq.hpp"

using namespace std;
using namespace cpplinq;

class HelloFunctions
{
public:
	static int parseFile(int* arr, int length, int pos)
	{
		int sum1 = 0;
		for (int i = 0; i < length; i++)
		{
			
			if (arr[i] == 0)
			{
				sum1 += arr[i];
			}
		}

		int* arr2;
		arr2 = new int[length];
		for (int i = 0; i < length; i++)
		{
			arr2[i] = i;
			sum1 += 1;
		}
		delete arr2;



		// LINQ.
		int ints[] = { 3,2,3,8,2,4,4 };
		auto result = from_array(ints)
			>> where([](int i) {return i % 2 == 0; })
			>> sum()
			;
		cout << "LINQ1:" << result << " - " << pos << endl;

		auto count_result =
			from_array(ints)
			>> where([](int g) { return g != 4; })
			>> select([](int g) { return g + 10; })
			>> distinct()
			>> count();
		cout << "LINQ2:" << count_result << " - " << pos << endl;


		return result;
	}
};

// Define C functions for the C++ class - as ctypes can only talk to C...
extern "C"
{
	__declspec(dllexport) int __cdecl parseFileCpp(int* arr, int length, int pos)
	{
		//cout << "calling: parseFileCpp" << endl;
		//cout << "arr: " << arr << endl;
		//cout << "len: " << length << endl;
		return HelloFunctions::parseFile(arr, length, pos);
	}

	__declspec(dllexport) int __cdecl parseFileC(int* arr, int length, int pos)
	{
		int sum2 = 0;
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == 0)
			{
				sum2 += arr[i];
			}
		}

		int* arr2 = (int*)malloc(length * sizeof(int));
		for (int i = 0; i < length; i++)
		{
			*(arr2 + i) = i;
			sum2 += 1;
		}
		free(arr2);

		return sum2 + pos;
	}
}
