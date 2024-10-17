#include "password.h"

#include <cstdint>
#include <string>
#include <iostream>
#include <openssl/sha.h>

Password* Password::createFromPassword(int64_t id, std::string name, std::string username, std::string password) {
	std::string encryptedName = _encrypt("name", name);
	std::string encryptedUsername = _encrypt("username", username);
	std::string encryptedPassword = _encrypt("password", password);
	return new Password(id, name, username, password, encryptedName, encryptedUsername, encryptedPassword);
}

Password* Password::createFromEncryptedPassword(int64_t id, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword) {
	std::string name = _decrypt("name", encryptedName);
	std::string username = _decrypt("username", encryptedUsername);
	std::string password = _decrypt("password", encryptedPassword);
	return new Password(id, name, username, password, encryptedName, encryptedUsername, encryptedPassword);
}

void Password::print() const {
	std::cout << "Name    : " << _name << "\n";
	std::cout << "Username: " << _name << "\n";
	std::cout << "Password: " << _name << "\n";
}

void Password::updateName(std::string name) {
	_name = name;
	_encryptedName = _encrypt("name", name);
}

void Password::updateUsername(std::string username) {
	_username = username;
	_encryptedUsername = _encrypt("username", username);
}

void Password::updatePassword(std::string password) {
	_password = password;
	_encryptedPassword = _encrypt("password", password);
}

std::string Password::_simpleEncryption(std::string value1, std::string value2) {
	std::string encryptedString = "";
	for (int64_t i = 0; i < value1.size(); i++) {
		char asciiChar1 = value1[i];
		char asciiChar2 = value2[i];
		// The keyboard chars are ascii chars from 32-176
		char keyboardChar1 = asciiChar1 - 32;
		char keyboardChar2 = asciiChar2 - 32;
		char encryptedKeyboardChar = keyboardChar1 + keyboardChar2;
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 176 - 32;
		if (encryptedKeyboardChar > MAX_KEYBOARD_CHAR_VALUE) encryptedKeyboardChar %= (MAX_KEYBOARD_CHAR_VALUE + 1);
		char asciiEncryptedChar = encryptedKeyboardChar + 32;
		encryptedString += asciiEncryptedChar;
	}
	return encryptedString;
}

std::string Password::_simpleDecryption(std::string encryptedValue1, std::string encryptedValue2) {
	std::string decryptedString = "";
	for (int64_t i = 0; i < encryptedValue1.size(); i++) {
		char encryptedAsciiChar1 = encryptedValue1[i];
		char encryptedAsciiChar2 = encryptedValue2[i];
		// The keyboard chars are ascii chars from 32-176
		char encryptedKeyboardChar1 = encryptedAsciiChar1 - 32;
		char encryptedKeyboardChar2 = encryptedAsciiChar2 - 32;
		char keyboardChar = encryptedKeyboardChar1 - encryptedKeyboardChar2;
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 176 - 32;
		keyboardChar += MAX_KEYBOARD_CHAR_VALUE;
		if (keyboardChar > MAX_KEYBOARD_CHAR_VALUE) keyboardChar %= (MAX_KEYBOARD_CHAR_VALUE + 1);
		char asciiChar = keyboardChar + 32;
		decryptedString += asciiChar;
	}
	return decryptedString;
}

std::string Password::_hash(std::string value) {

}
/*
		std::string _encrypt(std::string fieldName, std::string value);
		std::string _decrypt(std::string fieldName, std::string encryptedValue);

		std::string _hash(std::string value);
};
*/