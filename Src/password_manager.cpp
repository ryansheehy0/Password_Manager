#include "../Include/passwords.h"
#include "../Include/generate_password.h"
#include <iostream>
#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>

/*To Do:
	- Test and user interface
		- Get Password
		- Delete Password
		+ Add Password
		- Update Password
		+ Generate Password
	- Test each of the classes
		+ Add password(Problem)
			+ Creating new id
			+ Getting each field
			+ Creating password
				+ _encrypt(Problem)
					+ hash(Needs to be manually checked)
					+ simple encryption(Problem) Overflows char. Needs to be uint8_ts
			+ Writing to file
		- Get Password(Problem)

*/

std::string hiddenInput();

const std::string FILE_NAME = "my_passwords.txt";

enum class Operation {
	GET_PASSWORD,
	DELETE_PASSWORD,
	ADD_PASSWORD,
	UPDATE_PASSWORD,
	GENERATE_PASSWORD,
	EXIT
};

int main() {
	// Get master password
	std::cout << "Master password: ";
	std::string masterPassword = hiddenInput();
	// Get passwords
	Passwords passwords(FILE_NAME, masterPassword);

	while (true) {
		std::cout << "\n";
		std::cout << "0) Get Password\n";
		std::cout << "1) Delete Password\n";
		std::cout << "2) Add Password\n";
		std::cout << "3) Update Password\n";
		std::cout << "4) Generate Password\n";
		std::cout << "What would you like to do? ";
		Operation operation;
		std::string line; getline(std::cin, line);
		try {
			operation = static_cast<Operation>(std::stoi(line));
		} catch(...) {
			operation = Operation::EXIT;
		}

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
			case Operation::EXIT:
			default:
				return 1;
		}
	}
}

std::string hiddenInput() {
	struct termios oldAttributes, newAttributes;
	tcgetattr(STDIN_FILENO, &oldAttributes); // Get current terminal attributes
	newAttributes = oldAttributes;
	newAttributes.c_lflag &= ~ECHO; // Disable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &newAttributes); // Implement new terminal attributes
	std::string line; getline(std::cin, line);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldAttributes); // Restore terminal attributes
	std::cout << "\n";
	return line;
}