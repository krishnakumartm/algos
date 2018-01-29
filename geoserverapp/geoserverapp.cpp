// geoserverapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, wchar_t** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, (char**)nullptr);
}

