// testdouble.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest\gtest.h>
#include <Windows.h>
#include <atlstr.h>
static ATL::CAtlStringA GenerateKey256()
{
	HRESULT hResult;
	ATL::CAtlStringA szHex;
	GUID guid[2] = { 0 };

	do
	{
		hResult = CoCreateGuid(&guid[0]);
		if (FAILED(hResult))
			break;

		hResult = CoCreateGuid(&guid[1]);
		if (FAILED(hResult))
			break;

		// Convert to hex string
		char hex[10];
		unsigned char *pPtrGuid = (unsigned char*)guid;
		for (int i = 0; i <= 31; i++)
		{
			sprintf(hex, "%02X", pPtrGuid[i]);
			szHex += hex;
		}

	} while (false);

	return szHex;
}

int main(int argc, wchar_t** argv)
{
	testing::InitGoogleTest(&argc, argv);
	CoInitialize(NULL);
	GenerateKey256();
	CoUninitialize();

	RUN_ALL_TESTS();
    return 0;
}

