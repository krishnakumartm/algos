#include <gmock\gmock.h>
#include "Soundex.h"

using testing::Eq;

class SoundexEncoding : public testing::Test
{
public:
	SoundexEncoding();
	~SoundexEncoding();

private:
public:
	Soundex oSoundex;
};

SoundexEncoding::SoundexEncoding()
{
}

SoundexEncoding::~SoundexEncoding()
{
}

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	ASSERT_THAT(oSoundex.encode(L"A"), Eq(L"A000"));
}

TEST_F(SoundexEncoding, PadWithZerosToEnsureThreeDigits)
{
	ASSERT_THAT(oSoundex.encode(L"I"), Eq(L"I000"));
}

TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigit)
{
	ASSERT_THAT(oSoundex.encode(L"Ax"), Eq(L"A200"));
}

TEST_F(SoundexEncoding, IgnoreNonAlphabets)
{
	ASSERT_THAT(oSoundex.encode(L"A#"), Eq(L"A000"));
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonentsWithDigits)
{
	ASSERT_THAT(oSoundex.encode(L"Acdl"), Eq(L"A234"));
}