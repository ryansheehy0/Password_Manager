#include "../Include/generate_password.h"
#include <iostream>
#include <openssl/rand.h>

// Private:---------------------------------------------------------------------
bool GeneratePassword::_doYouWantToInclude(std::string str) {
	std::cout << "Do you want to include " << str << "? (y/n): ";
	char result;
	std::cin >> result;
	switch (result) {
		case 'Y':
		case 'y':
			return true;
			break;
		default:
			return false;
	}
}

int8_t GeneratePassword::_randomByte() {
	unsigned char randomByte;
	return RAND_bytes(&randomByte, 1);
}

char GeneratePassword::_randomChar(std::string str) {
	double randomNumFrom0to1 = _randomByte() / static_cast<double>(256);
	return str[randomNumFrom0to1 * str.size()];
}

std::string GeneratePassword::_generateRandomPassword(int64_t length, bool includeUpperCase, bool includeNumbers, bool includeSpecialChars, bool includeSpaces) {
	std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
	std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string numbers = "0123456789";
	std::string specialChars = "`~!@#$%^&*()_-+={[}]|\\:;\"'<,>.?/";
	// Get all the usable characters
	std::string usableCharacters = lowerCase; // Always include lower case characters
	if (includeUpperCase) usableCharacters += upperCase;
	if (includeNumbers) usableCharacters += numbers;
	if (includeSpecialChars) usableCharacters += specialChars;
	if (includeSpaces) usableCharacters += " ";
	// Generate random password
	std::string randomPassword = "";
	for (int i = 0; i < length + 1; i++) {
		randomPassword += _randomChar(usableCharacters);
	}
	// Return random password
	return randomPassword;
}

// Public:----------------------------------------------------------------------

void GeneratePassword::generatePassword() {
	std::cout << "Password length (max 64 characters): ";
	int64_t length;
	std::cin >> length;
	bool includeUpperCase = _doYouWantToInclude("upper case characters");
	bool includeNumbers = _doYouWantToInclude("numbers");
	bool includeSpecialChars = _doYouWantToInclude("special characters");
	bool includeSpaces = _doYouWantToInclude("spaces");
	std::cout << _generateRandomPassword(length, includeUpperCase, includeNumbers, includeSpecialChars, includeSpaces);
}