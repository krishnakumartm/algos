// recursiveMax.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>

int recursiveMax(int* arr, int arrSize)
{
	if (1 == arrSize)
		return arr[0];

	return fmax(recursiveMax(arr, arrSize - 1), arr[arrSize - 1]);
}


int main()
{
	int arr[] = { 3,6,2,4,9,2,5 };
	std::cout << recursiveMax(arr, 7);
    return 0;
}

