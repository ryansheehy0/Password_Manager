#include <iostream>
#include <string>
#include <vector>

/*To Do:
	- Make sure to prevent tabs from being imputed
	- Use getline instead of cin to allow for spaces
*/

/*
#include "password.h"
#include "fileToVector.h"
// Operations
#include "Operations/getPassword.h"
*/

const std::string FILE_NAME = "passwords.txt";

enum class Operation {
	EXIT,
	GET_PASSWORD,
	DELETE_PASSWORD,
	ADD_PASSWORD,
	UPDATE_PASSWORD,
	GENERATE_PASSWORD
};

int main() {
	/*
	std::vector<Password> passwords = fileToVector(FILE_NAME);
	std::string masterPassword;
	std::cout << "Master Password: ";
	std::cin >> masterPassword;
	*/

	while (true) {
		std::cout << "\n";
		std::cout << "0) Exit\n";
		std::cout << "1) Get Password\n";
		std::cout << "2) Delete Password\n";
		std::cout << "3) Add Password\n";
		std::cout << "4) Update Password\n";
		std::cout << "5) Generate Password\n";
		std::cout << "What would you like to do? ";
		int tempOperation = 0;
		std::cin >> tempOperation;
		Operation operation = static_cast<Operation>(tempOperation);

		switch (operation) {
			case Operation::EXIT:
				return 1;
			case Operation::GET_PASSWORD:
				std::cout << "Get password\n";
				break;
			case Operation::DELETE_PASSWORD:
				std::cout << "Delete password\n";
				break;
			case Operation::ADD_PASSWORD:
				std::cout << "Add password\n";
				break;
			case Operation::UPDATE_PASSWORD:
				std::cout << "Update password\n";
				break;
			case Operation::GENERATE_PASSWORD:
				std::cout << "Generate password\n";
				break;
			default:
				std::cout << "Has to be a number.\n";
				continue;
		}
	}
}