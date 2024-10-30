#include "password.h"

#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "ascii_keyboard_char.h"

// Constructor/Destructor-------------------------------------------------------

Password::Password(bool encryptedInput, int64_t id, std::string name, std::string username, std::string password, std::string masterPassword) {
	_id = id;
	_masterPassword = masterPassword;
	if (encryptedInput) {
		_encryptedName = name;
		_encryptedUsername = username;
		_encryptedPassword = password;
		_name = _decrypt("name", name);
		_username = _decrypt("username", username);
		_password = _decrypt("password", password);
	} else {
		_name = name;
		_username = username;
		_password = password;
		_encryptedName = _encrypt("name", name);
		_encryptedUsername = _encrypt("username", username);
		_encryptedPassword = _encrypt("password", password);
	}
}

// Private----------------------------------------------------------------------

std::string Password::_encrypt(std::string fieldName, std::string fieldValue) {
	// Create hash
	std::string hashInput = std::to_string(_id) + fieldName + _masterPassword;
	std::string hash = _hash(hashInput);
	// Make sure fieldValue is 64 characters in length
	while (fieldValue.size() != 64) { // Assumed to never be larger than 64 length
		fieldValue += " "; // Pad with spaces
	}
	// Return simple encryption
	return _simpleEncryption(hash, fieldValue);
}

std::string Password::_decrypt(std::string fieldName, std::string encryptedFieldValue) {
	// Create hash
	std::string hashInput = std::to_string(_id) + fieldName + _masterPassword;
	std::string hash = _hash(hashInput);
	// Return simple decryption
	return _simpleDecryption(hash, encryptedFieldValue);
}

std::string Password::_simpleEncryption(std::string value1, std::string value2) { // The length of value1 is assumed to be the same as value2
	std::string encryptedString = "";
	// Loop through each character
	for (int64_t i = 0; i < value1.size(); i++) {
		char asciiChar1 = value1[i];
		char asciiChar2 = value2[i];
		// Convert to keyboard chars. The keyboard chars are ascii chars from 32-176.
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 127 - 32;
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
		// Add ascii encrypted char to encrypted string
		encryptedString += asciiEncryptedChar;
	}
	// Return encrypted string
	return encryptedString;
}

std::string Password::_simpleDecryption(std::string encryptedValue1, std::string encryptedValue2) { // The length of value1 is assumed to be the same as value2
	std::string decryptedString = "";
	// Loop through each character
	for (int64_t i = 0; i < encryptedValue1.size(); i++) {
		char encryptedAsciiChar1 = encryptedValue1[i];
		char encryptedAsciiChar2 = encryptedValue2[i];
		// Convert ascii chars to keyboard chars
		const int64_t MAX_KEYBOARD_CHAR_VALUE = 127 - 32;
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
		// Add ascii char to decrypted string
		decryptedString += asciiChar;
	}
	// Return decrypted string
	return decryptedString;
}

std::string Password::_sha512(const std::string& input) { // Returns in hex
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
	// Get repeated sha512s
	std::string repeatedSha512 = input;
	for(int64_t i = 0; i < ROUNDS; i++) {
		repeatedSha512 = _sha512(repeatedSha512);
	}
	// Convert sha512's 128 hex characters to 64 keyboard characters
	std::string keyboardCharHash;
	for (int64_t i = 0; i < 64; i++) {
		// Get 2 hex characters at a time
		char hex1 = repeatedSha512[i * 2];
		char hex2 = repeatedSha512[i * 2 + 1];
		// Convert and add to keyboard char hash
		keyboardCharHash += AsciiKeyboardChar::hexesToAsciiKeyboardChar(hex1, hex2);
	}
	return keyboardCharHash;
}

// Public-----------------------------------------------------------------------

void Password::print() const {
	std::cout << "Name    : " << _name << "\n";
	std::cout << "Username: " << _username << "\n";
	std::cout << "Password: " << _password << "\n";
}

void Password::updateName(std::string newName) {
	_name = newName;
	_encryptedName = _encrypt("name", newName);
}

void Password::updateUsername(std::string newUsername) {
	_username = newUsername;
	_encryptedUsername = _encrypt("username", newUsername);
}

void Password::updatePassword(std::string newPassword) {
	_password = newPassword;
	_encryptedPassword = _encrypt("password", newPassword);
}