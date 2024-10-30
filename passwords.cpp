#include "passwords.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

// Constructors/Destructors ----------------------------------------------------

Passwords::Passwords(std::string fileName, std::string masterPassword) : _fileName(fileName), _masterPassword(masterPassword) {
	// Open file
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		std::cout << "Error opening " << fileName << "\n";
		exit(1);
	}
	// Create passwords vector from file
	int64_t id;
	std::string idString;
	std::string encryptedName;
  std::string encryptedUsername;
	std::string encryptedPassword;
	while (true) {
		// If there isn't another password, then break
		if (!getline(inputFile, idString)) break;
		getline(inputFile, encryptedName);
		getline(inputFile, encryptedUsername);
		getline(inputFile, encryptedPassword);
		// Check if the fields are correct
		if (encryptedName.size() != 64 || encryptedUsername.size() != 64 || encryptedPassword.size() != 64) {
			std::cout << "Error in " << fileName << "\n";
			exit(1);
		}
		try {id = std::stoi(idString);}
		catch (...) {
			std::cout << "Error in " << fileName << "\n";
			exit(1);
		}
		// Create new password on the heap
		Password* newPasswordPtr = new Password(true/*encrypted*/, id, encryptedName, encryptedUsername, encryptedPassword, masterPassword);
		// Add new password onto the passwords
		_passwords.push_back(newPasswordPtr);
	}
	// Close file
	inputFile.close();
}

Passwords::~Passwords() {
	for (Password* password : _passwords) {
		delete password;
	}
}

// Private:---------------------------------------------------------------------

int64_t Passwords::_askForPasswordIndex() const {
	// Print out each of the passwords with their corrsponding index(not id).
	for (int64_t i = 0; i < _passwords.size(); i++) {
		Password* password = _passwords[i];
		std::cout << i << ") " << password->name() << "\n";
	}
	// Get user's input
	std::cout << "Which password do you want to select? ";
	int64_t input;
	std::cin >> input;
	if (!(input >= 0 && input < _passwords.size())) {
		return -1; // Invalid input
	}
	// Return the password index
	return input;
}

std::string Passwords::_askForStringField(std::string fieldName) const {
	std::string fieldValue;
	// Repeatedly ask for the field value until it's correct
	while (true) {
		std::cout << "Password's " << fieldName << ": ";
		std::getline(std::cin, fieldValue); // Allow for whitespace
		// Make sure fieldValue doesn't have any tabs
		if (fieldValue.find('\t') != std::string::npos) {
			std::cout << fieldName << " cannot include tabs.\n";
			continue;
		}
		// Make sure fieldValue is the correct length
		if (fieldValue.size() > 64) {
			std::cout << fieldName << " must be less than or equal to 64 characters.\n";
			continue;
		}
		// Pad the field with spaces until it's 64 characters
		while (fieldValue.size() != 64) {
		 fieldValue += " ";
		}
		// Return fieldValue
		return fieldValue;
	}
}

bool Passwords::_doYouWantToUpdateField(std::string fieldName) const {
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

void Passwords::writeToFile() const {
	// Open file
	std::ofstream outputFile(_fileName);
	if (!outputFile) {
		std::cout << "Error opening " << _fileName << "\n";
		exit(1);
	}
	// Write passwords to output file
	for (Password* password : _passwords) {
		outputFile << password->id() << "\n"
							 << password->encryptedName() << "\n"
							 << password->encryptedUsername() << "\n"
							 << password->encryptedPassword() << "\n";
	}
	// Close file
	outputFile.close();
}

// Public:----------------------------------------------------------------------

void Passwords::printPassword() const {
	int64_t passwordIndex = _askForPasswordIndex();
	if (passwordIndex == -1) return;
	std::cout << "\n";
	_passwords[passwordIndex]->print();
}

void Passwords::deletePassword() {
	int64_t passwordIndex = _askForPasswordIndex();
	if (passwordIndex == -1) return;
	// Remove from heap
	delete _passwords[passwordIndex];
	// Remove from vector
	_passwords.erase(_passwords.begin() + passwordIndex);
	// Write passwords to file
	writeToFile();
}

void Passwords::addPassword() {
	// Get the next id
	int64_t id = 0;
	if (_passwords.size() != 0) {
		id = _passwords[_passwords.size() - 1]->id() + 1;
	}
	// Get each of the fields
	std::string name = _askForStringField("name");
	std::string username = _askForStringField("username");
	std::string password = _askForStringField("password");
	// Create new password on the heap
	Password* newPasswordPtr = new Password(false/*Encrypted*/, id, name, username, password, _masterPassword);
	// Add new password onto the vector
	_passwords.push_back(newPasswordPtr);
	// Write passwords to file
	writeToFile();
}

void Passwords::updatePassword() {
	int64_t passwordIndex = _askForPasswordIndex();
	// Update name
	if (_doYouWantToUpdateField("name")) {
		std::string newName = _askForStringField("new name");
		_passwords[passwordIndex]->updateName(newName);
	}
	// Update username
	if (_doYouWantToUpdateField("username")) {
		std::string newUsername = _askForStringField("new username");
		_passwords[passwordIndex]->updateUsername(newUsername);
	}
	// Update password
	if (_doYouWantToUpdateField("password")) {
		std::string newPassword = _askForStringField("new password");
		_passwords[passwordIndex]->updatePassword(newPassword);
	}
	// Write passwords to file
	writeToFile();
}