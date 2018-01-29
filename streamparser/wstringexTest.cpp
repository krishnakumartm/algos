#include <gmock\gmock.h>
#include "wstringex.h"

class ACustomStringFormatter :public testing::Test
{
public:
	ACustomStringFormatter();
	~ACustomStringFormatter();

private:

};

ACustomStringFormatter::ACustomStringFormatter()
{
}

ACustomStringFormatter::~ACustomStringFormatter()
{
}

TEST_F(ACustomStringFormatter, FormatsLocalDateTime)
{
	wstringex strFormattedString;
	tm tmout = { 0 };
	time_t time(0);
	errno_t ret = localtime_s(&tmout, &time);
	strFormattedString.format(L"%02d\\%02d\\%02d %02d:%02d:%02d", tmout.tm_mon + 1, tmout.tm_mday, tmout.tm_year + 1900, tmout.tm_hour, tmout.tm_min, tmout.tm_sec);

	//wstring strXML = strFormattedString.ToXML();
}