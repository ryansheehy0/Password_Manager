#include <string>
#include <fstream>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "passwords.h"
#include "generate_password.h"

using std::string;
using std::fstream;
using std::cout;
using std::cin;
using std::stoi;

const string FILE_NAME = ".passwords";

enum class Operation {
	GET_PASSWORD,
	DELETE_PASSWORD,
	ADD_PASSWORD,
	UPDATE_PASSWORD,
	GENERATE_PASSWORD,
	EXIT
};

string getMasterPassword();

int main() {
	string masterPassword = getMasterPassword();
	Passwords passwords = Passwords(FILE_NAME, masterPassword);

	while (true) {
		cout << "\n";
		cout << "0) Get Password\n";
		cout << "1) Delete Password\n";
		cout << "2) Add Password\n";
		cout << "3) Update Password\n";
		cout << "4) Generate Password\n";
		cout << "What would you like to do? ";
		Operation operation;
		string line;
		getline(cin, line);
		cout << "\n";
		try {
			operation = static_cast<Operation>(stoi(line));
		} catch(...) {
			operation = Operation::EXIT;
		}

		switch (operation) {
			case Operation::GET_PASSWORD:
				//passwords.printPassword();
				break;
			case Operation::DELETE_PASSWORD:
				//passwords.deletePassword();
				break;
			case Operation::ADD_PASSWORD:
				//passwords.addPassword();
				break;
			case Operation::UPDATE_PASSWORD:
				//passwords.updatePassword();
				break;
			case Operation::GENERATE_PASSWORD:
				GeneratePassword::generatePassword();
				break;
			case Operation::EXIT:
			default:
				return 1;
		}
	}
}

string getMasterPassword() {
	cout << "Master password: ";
	string masterPassword;
	// Set hidden input
	struct termios oldAttributes, newAttributes;
	tcgetattr(STDIN_FILENO, &oldAttributes); // Get current terminal attributes
	newAttributes = oldAttributes;
	newAttributes.c_lflag &= ~ECHO; // Disable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &newAttributes); // Implement new terminal attributes
	getline(cin, masterPassword);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldAttributes); // Restore terminal attributes
	cout << "\n";
	return masterPassword;
}