#pragma once
#include <gtest\gtest.h>
int main(int argc, wchar_t** argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}