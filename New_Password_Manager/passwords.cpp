#include "passwords.h"
#include "password.h"
#include <string>
#include <iostream>

using std::stoi;
using std::cout;
using std::cin;
using std::ofstream;

// Constructor -----------------------------------------------------------------
Passwords::Passwords(string fileName, string masterPassword) {
	fstream file(fileName);
	if (!file) {
		cout << "Error opening " << fileName << "\n";
		exit(1);
	}
	_fileName = fileName;
	_masterPassword = masterPassword;
	// Go through each line of the file and create passwords
	string line;
	while (getline(file, line)) {
		int id;
		try {
			id = stoi(line);
		} catch(...) {
			cout << "Error with password id in file.\n";
			exit(1);
		}
		getline(file, line);
		string encryptedName = line;
		getline(file, line);
		string encryptedUsername = line;
		getline(file, line);
		string encryptedPassword = line;
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
	cout << "Deleted:\n";
	_passwords[index].print();
	_passwords.erase(_passwords.begin() + index);
	_writeToFile();
}

void Passwords::addPassword() {
	int id = _passwords[_passwords.size() - 1].id() + 1;
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
	for (int i = 0; i < _passwords.size(); i++) {
		Password password = _passwords[i];
		std::cout << i << ") " << password.name() << "\n";
	}
	std::cout << "Which password do you want to select? ";
	int input;
	string line;
	getline(cin, line);
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
			cout << "  Must be less than or equal to 64 characters.\n";
			continue;
		}
		line.resize(64, ' ');
		return line;
	}
}

bool Passwords::_doYouWantToUpdateField(string fieldName) const {
	cout << "Do you ant to update " << fieldName << "? (y/n): ";
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
	ofstream file(_fileName);
	if (!file) {
		cout << "Error opening " << _fileName << "\n";
		exit(1);
	}
	for (const Password& password : _passwords) {
		file << password.id() << "\n"
		     << password.encryptedName() << "\n"
		     << password.encryptedUsername() << "\n"
		     << password.encryptedPassword() << "\n";
	}
	file.close();
}