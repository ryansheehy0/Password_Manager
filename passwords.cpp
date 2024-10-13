#include "passwords.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int64_t Passwords::_getIdField(std::ifstream* inputFile, int64_t* lineNum) {
	std::string idString;
	if (!getline(*inputFile, idString)) {
		std::cout << "Error on line number " << (*lineNum) << "\n";
		exit(1);
	}
	// Convert to int64_t
	(*lineNum)++;
}

std::string Passwords::_getStringField(std::ifstream* inputFile, int64_t* lineNum) {
	std::string field;
	if (!getline(*inputFile, field)) {
		std::cout << "Error on line number " << (*lineNum) << "\n";
		exit(1);
	}
	if (field.size() != 64) {
		std::cout << "Error on line number " << (*lineNum) << "\n";
		exit(1);
	}
	(*lineNum)++;
}

Passwords::Passwords(std::string fileName) : _fileName(fileName) {
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		std::cout << "Error opening " << fileName << "\n";
		exit(1);
	}
	int64_t lineNum = 1;
	while (true) {
		int64_t id = _getIdField(&inputFile, &lineNum);
		std::string encryptedName = _getStringField(&inputFile, &lineNum);
		std::string encryptedUsername = _getStringField(&inputFile, &lineNum);
		std::string encryptedPassword = _getStringField(&inputFile, &lineNum);
		Password* passwordPtr = Password::createFromEncryptedPassword(id, encryptedName, encryptedUsername, encryptedPassword);
		_passwords.push_back(passwordPtr);
	}
	inputFile.close();
}

Passwords::~Passwords() {
	for (Password* password : _passwords) {
		delete password;
	}
}

int64_t Passwords::_askUserForPasswordIndex() {
	for (int64_t i = 0; i < _passwords.size(); i++) {
		Password* password = _passwords[i];
		std::cout << i << ") " << password->name() << "\n";
	}
	std::cout << "Which password do you want to select? ";
	int64_t input;
	std::cin >> input;
	if (input < 0 || input >= _passwords.size()) {
		return -1;
	}
	return input;
}

void Passwords::getPassword() {
	int64_t passwordIndex = _askUserForPasswordIndex();
	if (passwordIndex == -1) return;
	std::cout << "\n";
	_passwords[passwordIndex]->print();
}

void Passwords::deletePassword() {
	int64_t passwordIndex = _askUserForPasswordIndex();
	if (passwordIndex == -1) return;
	// Maybe ask again if they want to delete.
	_passwords.erase(_passwords.begin() + passwordIndex);
}

std::string Passwords::_askForStringField(std::string fieldName) {
	std::string field;
	while (true) {
		std::cout << "Password's " << fieldName << ": ";
		std::cin >> field;
		if (field.size() > 64) {
			std::cout << fieldName << " must be less than or equal to 64 characters.\n";
			continue;
		}
		// Pad the field with spaces until it's 64 characters
		while (field.size() != 64) {
		 field += " ";
		}
		return field;
	}
}

void Passwords::addPassword() {
	// Get the next id
	int64_t id = 0;
	if (_passwords.size() != 0) {
		id = _passwords[_passwords.size() - 1]->id() + 1;
	}

	std::string name = _askForStringField("Name");
	std::string username = _askForStringField("Username");
	std::string password = _askForStringField("Password");

	Password* newPassword = Password::createFromPassword(id, name, username, password);
	_passwords.push_back(newPassword);
}

bool Passwords::_doYouWantToUpdateField(std::string fieldName) {
	std::cout << "Do you want to update the " << fieldName << "? (y/n): ";
	char response;
	std::cin >> response;
	switch (response) {
		case 'y':
		case 'Y':
			return true;
		default:
			return false;
	}
}

void Passwords::updatePassword() {
	int64_t passwordIndex = _askUserForPasswordIndex();

	bool updateName = _doYouWantToUpdateField("name");
	if (updateName) {
		std::string newName = _askForStringField("New Name");
		_passwords[passwordIndex]->updateName(newName);
	}

	bool updateUsername = _doYouWantToUpdateField("username");
	if (updateUsername) {
		std::string newUsername = _askForStringField("New Username");
		_passwords[passwordIndex]->updateUsername(newUsername);
	}

	bool updatePassword = _doYouWantToUpdateField("password");
	if (updatePassword) {
		std::string newPassword = _askForStringField("New Password");
		_passwords[passwordIndex]->updatePassword(newPassword);
	}
}