#include <gmock\gmock.h>

class Soundex
{
public:
	Soundex();
	~Soundex();

private:

};

Soundex::Soundex()
{
}

Soundex::~Soundex()
{
}

TEST(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	Soundex oSoundex;
}