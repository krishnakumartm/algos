#ifndef SOUNDEX_H
#define SOUNDEX_H
#include <string>
#include <unordered_map>

static const size_t MaxCodeLength{ 4 };
class Soundex
{
public:
	std::wstring encode(const std::wstring& word)
	{
		return zeropad(head(word) + encodedDigits(tail(word)));
	}
private:
	std::wstring zeropad(const std::wstring& word)
	{
		auto zerosNeeded = MaxCodeLength - word.length();
		return word + std::wstring(zerosNeeded, '0');
	}

	std::wstring head(const std::wstring& word)
	{
		return word.substr(0, 1);
	}

	std::wstring tail(const std::wstring& word)
	{
		return word.substr(1);
	}

	std::wstring encodedDigits(const std::wstring& word)
	{
		std::wstring encoding;
		for (auto letter : word)
		{
			encoding += encodedDigit(letter);
		}
		return encoding;
	}

	std::wstring encodedDigit(wchar_t letter)
	{
		static const std::unordered_map<wchar_t, std::wstring> encodings = {
			{ L'b', L"1" }, { L'f', L"1" }, { L'p', L"1" }, { L'v', L"1" },
			{ L'c', L"2" }, { L'g', L"2" }, { L'j', L"2" }, { L'k', L"2" }, { L'q', L"2" }, { L's', L"2" }, { L'x', L"2" }, { L'z', L"2" },
			{ L'd', L"3" }, { L't', L"3" },
			{ L'l', L"4" },
			{ L'm', L"5" }, { L'n', L"5" },
			{ L'r', L"6" }
		};
		auto itr = encodings.find(letter);
		return itr != encodings.end() ? itr->second:L"";
	}
};



#endif // !SOUNDEX_H
