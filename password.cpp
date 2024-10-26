#include "password.h"

#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "keyboard_char.h"

Password::Password(int64_t id, std::string name, std::string username, std::string password, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword, std::string masterPassword) : _id(id), _name(name), _username(username), _password(password), _encryptedName(encryptedName), _encryptedUsername(encryptedUsername), _encryptedPassword(encryptedPassword), _masterPassword(masterPassword) {}

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

std::string Password::_encrypt(std::string fieldName, std::string fieldValue, std::string masterPassword, int64_t id) {
	std::string hashInput = std::to_string(id) + fieldName + masterPassword;
	std::string hash = _hash(hashInput);
	// Make sure fieldValue is 64 characters in length
	while (fieldValue.size() != 64) {
		// Pad with spaces
		fieldValue += " ";
	}
	return _simpleEncryption(hash, fieldValue);
}

std::string Password::_decrypt(std::string fieldName, std::string encryptedFieldValue, std::string masterPassword, int64_t id) {
	std::string hashInput = std::to_string(id) + fieldName + masterPassword;
	std::string hash = _hash(hashInput);
	return _simpleDecryption(hash, encryptedFieldValue);
}

void Password::print() const {
	std::cout << "Name    : " << _name << "\n";
	std::cout << "Username: " << _username << "\n";
	std::cout << "Password: " << _password << "\n";
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
	// The length of value1 is assumed to be the same as value2
	std::string encryptedString = "";
	for (int64_t i = 0; i < value1.size(); i++) {
		char asciiChar1 = value1[i];
		char asciiChar2 = value2[i];

		// Convert to keyboard chars. The keyboard chars are ascii chars from 32-176.
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 176 - 32;
		char keyboardChar1 = asciiChar1 - 32;
		char keyboardChar2 = asciiChar2 - 32;

		// Encrypt to get encrypted keyboard chars
		char encryptedKeyboardChar = keyboardChar1 + keyboardChar2;

		// Loop encrypted keyboard char if it overflows
		if (encryptedKeyboardChar > MAX_KEYBOARD_CHAR_VALUE) {
			encryptedKeyboardChar %= (MAX_KEYBOARD_CHAR_VALUE + 1);
		}

		// Convert keyboard back into ascii
		char asciiEncryptedChar = encryptedKeyboardChar + 32;
		encryptedString += asciiEncryptedChar;
	}
	return encryptedString;
}

std::string Password::_simpleDecryption(std::string encryptedValue1, std::string encryptedValue2) {
	// The length of value1 is assumed to be the same as value2
	std::string decryptedString = "";
	for (int64_t i = 0; i < encryptedValue1.size(); i++) {
		char encryptedAsciiChar1 = encryptedValue1[i];
		char encryptedAsciiChar2 = encryptedValue2[i];

		// Convert ascii chars to keyboard chars
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 176 - 32;
		char encryptedKeyboardChar1 = encryptedAsciiChar1 - 32;
		char encryptedKeyboardChar2 = encryptedAsciiChar2 - 32;

		// Decrypt to get keyboard chars
		char keyboardChar = encryptedKeyboardChar1 - encryptedKeyboardChar2;
		keyboardChar += MAX_KEYBOARD_CHAR_VALUE;

		// Loop decrypted keyboard char if it overflows
		if (keyboardChar > MAX_KEYBOARD_CHAR_VALUE) {
			keyboardChar %= (MAX_KEYBOARD_CHAR_VALUE + 1);
		}

		// Convert keyboard chars back into ascii
		char asciiChar = keyboardChar + 32;
		decryptedString += asciiChar;
	}
	return decryptedString;
}

std::string Password::_sha512(const std::string& input) {
		unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

std::string Password::_hash(std::string input) {
	const int64_t ROUNDS = 50;

	// Get repeated sha512s of input
	std::string repeatedSha512 = input;
	for(int64_t i = 0; i < ROUNDS; i++) {
		repeatedSha512 = _sha512(repeatedSha512);
	}

	// Convert sha512 128 hex characters to 64 keyboard characters
	std::string keyboardCharHash;
	for (int64_t i = 0; i < 64; i++) {
		// Get hex characters 2 at a time
		char hex1 = repeatedSha512[i * 2];
		char hex2 = repeatedSha512[i * 2 + 1];
		keyboardCharHash += KeyboardChar::hexesToKeyboardChar(hex1, hex2);
	}

	return keyboardCharHash;
}