#pragma once

#include "password.h"
#include <vector>
#include <string>
#include <cstdint>

class PasswordList {
	private:
		std::vector<Password> _passwordList;

	public:
		PasswordList(std::string fileName);
		std::string 

		void printPassword(int64_t index);

		void deletePassword(int64_t index);

		void addPassword(Password password);

		void updatePassword(int64_t index);
};