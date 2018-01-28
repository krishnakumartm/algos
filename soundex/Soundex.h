#ifndef SOUNDEX_H
#define SOUNDEX_H
#include <string>
#include <unordered_map>
#include <cctype>

static const size_t MaxCodeLength{ 4 };
const std::wstring NotADigit{ L"*" };
class Soundex
{
public:
	std::wstring encode(const std::wstring& word)
	{
		return zeropad(upperFront(head(word)) + tail(encodedDigits(word)));
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

	std::wstring upperFront(const std::wstring& letter)
	{
		return std::wstring(1, std::toupper(static_cast<wchar_t>(letter.front())));
	}

	std::wstring lastDigit(const std::wstring& encoding)
	{
		if (encoding.empty())
			return NotADigit;

		return std::wstring(1, encoding.back());
	}

	void encodeHead(std::wstring& encoding, const std::wstring word)
	{
		encoding += encodedDigit(word.front());
	}

	void encodeTail(std::wstring& encoding, const std::wstring word)
	{
		for (auto index = 1u; index < word.length();  index++)
		{
			if (!isComplete(encoding))
				encodeLetter(encoding, word[index], word[index -1]);
		}
	}

	void encodeLetter(std::wstring& encoding, wchar_t letter, wchar_t previousLetter)
	{
		auto digit = encodedDigit(letter);
		if (digit != NotADigit && (digit != lastDigit(encoding) || isVowel(previousLetter)))
			encoding += digit;
	}

	bool isVowel(wchar_t letter)
	{
		return std::wstring(L"aeiou").find(lower(letter)) != std::wstring::npos;
	}

	std::wstring encodedDigits(const std::wstring& word)
	{
		std::wstring encoding;
		encodeHead(encoding, word);
		encodeTail(encoding, word);
		return encoding;
	}

	bool isComplete(std::wstring encoding)
	{
		return encoding.length() == MaxCodeLength;
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
		auto itr = encodings.find(lower(letter));
		return itr != encodings.end() ? itr->second : NotADigit;
	}

	wchar_t lower(wchar_t letter)
	{
		return std::tolower(static_cast<wchar_t>(letter));
	}
};



#endif // !SOUNDEX_H
