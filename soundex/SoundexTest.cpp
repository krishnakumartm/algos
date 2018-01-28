#include <gmock\gmock.h>
#include <gmock\gmock-matchers.h>
#include "Soundex.h"

using testing::Eq;
using testing::StartsWith;

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

TEST_F(SoundexEncoding, LimitLengthToFour)
{
	ASSERT_THAT(oSoundex.encode(L"Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoreVowelLikeLetters)
{
	ASSERT_THAT(oSoundex.encode(L"BaAeiIoOuUhHyYcdl"), Eq(L"B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
	//ASSERT_THAT(oSoundex.encodedDigit(L'b'), Eq(oSoundex.encodedDigit(L'f')));
	//ASSERT_THAT(oSoundex.encodedDigit(L'c'), Eq(oSoundex.encodedDigit(L'g')));
	//ASSERT_THAT(oSoundex.encodedDigit(L'd'), Eq(oSoundex.encodedDigit(L't')));
	ASSERT_THAT(oSoundex.encode(L"Abfcgdt"), Eq(L"A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
	ASSERT_THAT(oSoundex.encode(L"abcd"), StartsWith(L"A"));
}

TEST_F(SoundexEncoding, IgnoreCaseWhenEncodigConsonants)
{
	ASSERT_THAT(oSoundex.encode(L"BCDL"), Eq(oSoundex.encode(L"Bcdl")));
}

TEST_F(SoundexEncoding, CombineAdjecentDuplicateEncodings)
{
	ASSERT_THAT(oSoundex.encode(L"Bbcd"), Eq(L"B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeperatedByVowels)
{
	ASSERT_THAT(oSoundex.encode(L"Jbob"), Eq(L"J110"));
}