#include "password.h"
#include <openssl/sha.h>
#include <string>
#include <iostream>

using std::to_string;
using std::cout;

// Constructor -----------------------------------------------------------------
Password::Password(string masterPassword, int id, ArgType argType,
	string name,
	string username,
	string password
) {
	_masterPassword = masterPassword;
	_id = id;
	switch (argType) {
		case ArgType::ENCRYPTED:
			_name = _decrypt("name", name);
			_username = _decrypt("username", username);
			_password = _decrypt("password", password);
			_encryptedName = name;
			_encryptedUsername = username;
			_encryptedPassword = password;
			break;
		case ArgType::DECRYPTED:
			_name = name;
			_username = username;
			_password = password;
			_encryptedName = _encrypt("name", name);
			_encryptedUsername = _encrypt("username", username);
			_encryptedPassword = _encrypt("password", password);
			break;
	}
}

// Public ----------------------------------------------------------------------
void Password::updateName(string newName) {
	_name = newName;
	_encryptedName = _encrypt("name", newName);
}

void Password::updateUsername(string newUsername) {
	_username = newUsername;
	_encryptedUsername = _encrypt("username", newUsername);
}

void Password::updatePassword(string newPassword) {
	_password = newPassword;
	_encryptedPassword = _encrypt("password", newPassword);
}

void Password::print() const {
	cout << "Name    : " << _name << "\n";
	cout << "Username: " << _username << "\n";
	cout << "Password: " << _password << "\n";
}

// Private ---------------------------------------------------------------------
string Password::_encrypt(string fieldName, string value) const {
	string hash = _hash(to_string(_id) + fieldName + _masterPassword);
	string output = value;
	output.resize(64, ' '); // Pad with spaces
	for (int i = 0; i < 64; i++) {
		output[i] ^= hash[i];
	}
	return output;
}

string Password::_hash(string value) const {
	const int ROUNDS = 50;
	string repeatedSHA512 = value;
	for (int i = 0; i < ROUNDS; i++) {
		repeatedSHA512 = _sha512(repeatedSHA512);
	}
	return repeatedSHA512;
}

string Password::_sha512(string value) const {
	unsigned char hash[SHA512_DIGEST_LENGTH];
	SHA512(reinterpret_cast<const unsigned char*>(value.c_str()), value.size(), hash);
	return string(reinterpret_cast<char*>(hash), SHA512_DIGEST_LENGTH);
}