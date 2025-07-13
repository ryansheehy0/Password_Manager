#include "passwords.h"
#include "password.h"
#include <string>
#include <iostream>
#include <iomanip>

using std::stoi;
using std::cout;
using std::setw;
using std::right;

// Constructor -----------------------------------------------------------------
Passwords::Passwords(fstream file, string masterPassword) {
	_file = file;
	_masterPassword = masterPassword;
	// Go through each line of the file and create passwords
	string line;
	while (getline(_file, line)) {
		int id;
		try {
			id = stoi(line);
		} catch(...) {
			cout << "Error with password id in file.\n";
			exit(1);
		}
		getline(_file, line);
		string encryptedName = line;
		getline(_file, line);
		string encryptedUsername = line;
		getline(_file, line);
		string encryptedPassword = line;
		// Create password and add to vector
		Password password = Password(_masterPassword, id, ArgType::ENCRYPTED,
			encryptedName,
			encryptedUsername,
			encryptedPassword
		);
		_passwords.push_back(password);
	}
}

// Public ----------------------------------------------------------------------
void Passwords::printPassword() const {
	int index = _askForPasswordIndex();
	cout << setw(10) << "Name: " << right << _passwords[index].name() << "\n";
	cout << setw(10) << "Username: " << right << _passwords[index].username() << "\n";
	cout << setw(10) << "Password: " << right << _passwords[index].password() << "\n";
}

void Passwords::deletePassword() {
	
}

void Passwords::addPassword() {
	
}

void Passwords::updatePassword() {

}

// Private ---------------------------------------------------------------------
int _askForPasswordIndex() const {}
string _askForStringField(string fieldName) const{}
bool _doYouWantToUpdateField(string fieldName) const{}

void _writeToFile() const{}