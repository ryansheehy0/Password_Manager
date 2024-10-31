#include "passwords.h"
#include "generate_password.h"
#include <iostream>
#include <string>
#include <vector>

/*To Do:
	- Make make file
	- Test each of the classes
	- Make sure user interface is correct
*/

const std::string FILE_NAME = "passwords.txt";

enum class Operation {
	GET_PASSWORD,
	DELETE_PASSWORD,
	ADD_PASSWORD,
	UPDATE_PASSWORD,
	GENERATE_PASSWORD
};

int main() {
	// Get master password
	std::cout << "Master password: ";
	std::string masterPassword;
	std::cin >> masterPassword;
	// Get passwords
	Passwords passwords(FILE_NAME, masterPassword);

	while (true) {
		std::cout << "\n";
		std::cout << "0) Get Password\n";
		std::cout << "1) Delete Password\n";
		std::cout << "2) Add Password\n";
		std::cout << "2) Update Password\n";
		std::cout << "4) Generate Password\n";
		std::cout << "What would you like to do? ";
		int tempOperation = 0;
		std::cin >> tempOperation;
		Operation operation = static_cast<Operation>(tempOperation);

		switch (operation) {
			case Operation::GET_PASSWORD:
				passwords.printPassword();
				break;
			case Operation::DELETE_PASSWORD:
				passwords.deletePassword();
				break;
			case Operation::ADD_PASSWORD:
				passwords.addPassword();
				break;
			case Operation::UPDATE_PASSWORD:
				passwords.updatePassword();
				break;
			case Operation::GENERATE_PASSWORD:
				GeneratePassword::generatePassword();
				break;
			default:
				return 1;
		}
	}
}