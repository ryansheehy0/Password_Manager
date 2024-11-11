#pragma once

#include <string>

class GeneratePassword {
	private:
		static bool _doYouWantToInclude(std::string str);
		static uint8_t _randomByte();
		static char _randomChar(std::string str);
		static std::string _generateRandomPassword(int64_t length, bool includeUpperCase, bool includeNumbers, bool includeSpecialChars, bool includeSpaces);
	public:
		static void generatePassword();
};
