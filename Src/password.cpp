#include "../Include/password.h"
#include "../Include/ascii_keyboard_char.h"
#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstdint>

// Constructor/Destructor-------------------------------------------------------

Password::Password(bool encryptedInput, int64_t id, std::string name, std::string username, std::string password, std::string masterPassword) {
	_id = id;
	_masterPassword = masterPassword;
	if (encryptedInput) {
		_encryptedName = name;
		_encryptedUsername = username;
		_encryptedPassword = password;
		_name = _encryptOrDecrypt(false, "name", name);
		_username = _encryptOrDecrypt(false, "username", username);
		_password = _encryptOrDecrypt(false, "password", password);
	} else {
		_name = name;
		_username = username;
		_password = password;
		_encryptedName = _encryptOrDecrypt(true, "name", name);
		_encryptedUsername = _encryptOrDecrypt(true, "username", username);
		_encryptedPassword = _encryptOrDecrypt(true, "password", password);
	}
}

// Private----------------------------------------------------------------------

std::string Password::_encryptOrDecrypt(bool encrypt, std::string fieldName, std::string fieldValue) {
	// Create hash
	std::string hashInput = std::to_string(_id) + fieldName + _masterPassword;
	std::string hash = _hash(hashInput);
	// Make sure fieldValue is 64 characters in length
	while (fieldValue.size() != 64) { // Assumed to never be larger than 64 length
		fieldValue += " "; // Pad with spaces
	}
	// Return encryption or decryption
	return _simpleEncryptionOrDecryption(encrypt, hash, fieldValue);
}

std::string Password::_simpleEncryptionOrDecryption(bool encrypt, std::string value1, std::string value2) {
	const uint8_t KEYBOARD_CHAR_SIZE = 127 - 32;
	std::string output = "";
	// Loop through each character
	for (int64_t i = 0; i < value1.size(); i++) {
		uint8_t asciiChar1 = value1[i];
		uint8_t asciiChar2 = value2[i];
		uint8_t keyboardChar1 = asciiChar1 - 32;
		uint8_t keyboardChar2 = asciiChar2 - 32;
		uint8_t outputKeyboardChar;
		if (encrypt) {
			outputKeyboardChar = keyboardChar1 + keyboardChar2;
		} else { // Decrypt
			outputKeyboardChar = keyboardChar2 - keyboardChar1;
			outputKeyboardChar += KEYBOARD_CHAR_SIZE;
		}
		// Loop output keyboard char if it overflows
		outputKeyboardChar %= KEYBOARD_CHAR_SIZE;
		// Add to output
		uint8_t outputAsciiChar = outputKeyboardChar + 32;
		output += outputAsciiChar;
	}
	return output;
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
	_encryptedName = _encryptOrDecrypt(true, "name", newName);
}

void Password::updateUsername(std::string newUsername) {
	_username = newUsername;
	_encryptedUsername = _encryptOrDecrypt(true, "username", newUsername);
}

void Password::updatePassword(std::string newPassword) {
	_password = newPassword;
	_encryptedPassword = _encryptOrDecrypt(true, "password", newPassword);
}