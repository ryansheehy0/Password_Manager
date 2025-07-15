#include "passwords.h"
#include "password.h"
#include <string>
#include <iostream>
#include <fstream>

using std::stoi;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::ios;

// Constructor -----------------------------------------------------------------
Passwords::Passwords(string fileName, string masterPassword) {
	ifstream file(fileName, ios::binary);
	if (!file) {
		cout << "Error opening " << fileName << "\n";
		exit(1);
	}
	_fileName = fileName;
	_masterPassword = masterPassword;
	// Go through each line of the file and create passwords
	while (true) {
		int id;
		if (!file.read(reinterpret_cast<char *>(&id), sizeof(id))) break;
		string encryptedName(64, '\0');
		string encryptedUsername(64, '\0');
		string encryptedPassword(64, '\0');
		file.read(encryptedName.data(), 64);
		file.read(encryptedUsername.data(), 64);
		file.read(encryptedPassword.data(), 64);
		// Create password and add to vector
		Password password = Password(_masterPassword, id, ArgType::ENCRYPTED,
			encryptedName,
			encryptedUsername,
			encryptedPassword
		);
		_passwords.push_back(password);
	}

	file.close();
}

// Public ----------------------------------------------------------------------
void Passwords::printPassword() const {
	int index = _askForPasswordIndex();
	if (index == -1) return;
	_passwords[index].print();
}

void Passwords::deletePassword() {
	int index = _askForPasswordIndex();
	if (index == -1) return;
	cout << "Deleted\n";
	_passwords[index].print();
	_passwords.erase(_passwords.begin() + index);
	_writeToFile();
}

void Passwords::addPassword() {
	int id = 0;
	if (!_passwords.empty()) {
		id = _passwords[_passwords.size() - 1].id() + 1;
	}
	cout << "\n";
	string name = _askForStringField("name");
	string username = _askForStringField("username");
	string password = _askForStringField("password");
	Password newPassword = Password(_masterPassword, id, ArgType::DECRYPTED,
		name,
		username,
		password
	);
	_passwords.push_back(newPassword);
	_writeToFile();
}

void Passwords::updatePassword() {
	int index = _askForPasswordIndex();
	if (index == -1) return;
	if (_doYouWantToUpdateField("name")) {
		string newName = _askForStringField("new name");
		_passwords[index].updateName(newName);
	}
	if (_doYouWantToUpdateField("username")) {
		string newUsername = _askForStringField("new username");
		_passwords[index].updateUsername(newUsername);
	}
	if (_doYouWantToUpdateField("password")) {
		string newPassword = _askForStringField("new password");
		_passwords[index].updatePassword(newPassword);
	}
	_writeToFile();
}

// Private ---------------------------------------------------------------------
int Passwords::_askForPasswordIndex() const {
	cout << "\n";
	for (int i = 0; i < _passwords.size(); i++) {
		Password password = _passwords[i];
		cout << i << ") " << password.name() << "\n";
	}
	cout << "Which password do you want to select? ";
	int input;
	string line;
	getline(cin, line);
	cout << "\n";
	try {
		input = stoi(line);
	} catch (...) {
		return -1;
	}
	if (input >= _passwords.size() || input < 0) return -1;
	return input;
}

string Passwords::_askForStringField(string fieldName) const {
	while (true) {
		cout << "Password's " << fieldName << ": ";
		string line;
		getline(cin, line);
		if (line.size() > 64) {
			cout << "Must be less than or equal to 64 characters.\n";
			continue;
		}
		line.resize(64, ' ');
		return line;
	}
}

bool Passwords::_doYouWantToUpdateField(string fieldName) const {
	cout << "Do you want to update " << fieldName << "? (y/n): ";
	string line;
	getline(cin, line);
	switch (line[0]) {
		case 'Y':
		case 'y':
			return true;
		default:
			return false;
	}
}

void Passwords::_writeToFile() const {
	ofstream file(_fileName, ios::binary);
	if (!file) {
		cout << "Error opening " << _fileName << "\n";
		exit(1);
	}
	for (const Password& password : _passwords) {
		int id = password.id();
		file.write(reinterpret_cast<const char*>(&id), sizeof(id));
		file.write(password.encryptedName().data(), 64);
		file.write(password.encryptedUsername().data(), 64);
		file.write(password.encryptedPassword().data(), 64);
	}
	file.close();
}