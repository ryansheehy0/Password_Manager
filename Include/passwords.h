#pragma once

#include "password.h"
#include <cstdint>
#include <vector>
#include <string>

class Passwords {
	private:
		std::string _fileName;
		std::string _masterPassword;
		std::vector<Password*> _passwords;

		int64_t _askForPasswordIndex() const;
		std::string _askForStringField(std::string fieldName) const;
		bool _doYouWantToUpdateField(std::string fieldName) const;

		void writeToFile() const;

	public:
		Passwords(std::string fileName, std::string materPassword);
		~Passwords();

		void printPassword() const;
		void deletePassword();
		void addPassword();
		void updatePassword();
};