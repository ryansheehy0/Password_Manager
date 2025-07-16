#include "generate_password.h"
#include <iostream>
#include <openssl/rand.h>

using std::cout;
using std::cin;

void GeneratePassword::generatePassword() {
	cout << "\n";
	string password;

	string passwordCharacters = "abcdefghijklmnopqrstuvwxyz";
	const string UPPERCASE_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string SPECIAL_CHARACTERS = "!@#$%^&*()-_=+[]{}|\\:;\"'<>,.?/";
	const string NUMBER_CHARACTERS = "0123456789";

	int passwordLength = _getPasswordLength();

	// Uppercase letters
	int uppercaseIndex = -1;
	if (_doYouWantToInclude("uppercase letters")) {
		passwordCharacters += UPPERCASE_CHARACTERS;
		uppercaseIndex = _randomIndex(passwordLength);
	}

	// Special characters
	int specialIndex = -1;
	if (_doYouWantToInclude("special characters")) {
		passwordCharacters += SPECIAL_CHARACTERS;
		specialIndex = _randomIndex(passwordLength);
		if (specialIndex == uppercaseIndex) specialIndex = (specialIndex + 1) % passwordLength;
	}

	// Numbers
	int numbersIndex = -1;
	if (_doYouWantToInclude("numbers")) {
		passwordCharacters += NUMBER_CHARACTERS;
		numbersIndex = _randomIndex(passwordLength);
		if (numbersIndex == uppercaseIndex) numbersIndex = (numbersIndex + 1) % passwordLength;
		if (numbersIndex == specialIndex) numbersIndex = (numbersIndex + 1) % passwordLength;
		if (numbersIndex == uppercaseIndex) numbersIndex = (numbersIndex + 1) % passwordLength;
	}

	// Create password
	for (int i = 0; i < passwordLength; i++) {
		// Guarantee at least one included character
		if (i == uppercaseIndex) {
			password += UPPERCASE_CHARACTERS[_randomIndex(UPPERCASE_CHARACTERS.size())];
			continue;
		}
		if (i == specialIndex) {
			password += SPECIAL_CHARACTERS[_randomIndex(SPECIAL_CHARACTERS.size())];
			continue;
		}
		if (i == numbersIndex) {
			password += NUMBER_CHARACTERS[_randomIndex(NUMBER_CHARACTERS.size())];
			continue;
		}

		password += passwordCharacters[_randomIndex(passwordCharacters.size())];
	}

	// Print out password
	cout << "\n" << password << "\n";
}

bool GeneratePassword::_doYouWantToInclude(string fieldName) {
	cout << "Include " << fieldName << "? (y/n): ";
	string line;
	getline(cin, line);
	switch (line[0]) {
		case 'Y':
		case 'y':
			return true;
			break;
		default:
			return false;
	}
}

int GeneratePassword::_randomIndex(int length) {
	unsigned char randomByte;
	if (!RAND_bytes(&randomByte, 1)) {
		cout << "Failed to generate random password.\n";
		exit(1);
	}
	return randomByte % length;
}

int GeneratePassword::_getPasswordLength() {
	int length = 64;
	cout << "Password length (max 64): ";
	string line;
	getline(cin, line);
	try {
		length = std::stoi(line);
		if (length < 3 || length > 64) length = 64;
	} catch(...) {}
	return length;
}