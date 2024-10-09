#include "passwordList.h"

#include <fstream>
#include <stdio.h>
#include <cstdint>
#include <iostream>

PasswordList::PasswordList(std::string fileName) {
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		std::cout << "Error opening " << fileName << "\n";
		exit(1);
	}

	while (true) {
		std::string idLine;
		if (!getline(inputFile, idLine)) {
			// Error
		}
		// Convert to int64_t


		std::string line;
		int64_t id;
		std::string name;
		std::string username;
		std::string password;
		int64_t lineNum;
		while () {
			
		}
	}

	std::string line;

		// id
		// name
		// username
		// password
		// newline
	}

	Password pass(id, name, username, password);

	inputFile.close();
}



#include "password.h"
#include <vector>
#include <string>
#include <cstdint>

class PasswordList {
	private:
		std::vector<Password> _passwordList;

	public:
		PasswordList(std::string fileName);

		void printPassword(int64_t index);

		void deletePassword(int64_t index);

		void addPassword(Password password);

		void updatePassword(int64_t index);
};