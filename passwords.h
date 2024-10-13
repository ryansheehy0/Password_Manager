#pragma once

#include "password.h"

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

class Passwords {
	private:
		std::vector<Password*> _passwords;
		std::string _fileName;

		int64_t _askUserForPasswordIndex();

		int64_t Passwords::_getIdField(std::ifstream* inputFile, int64_t* lineNum);
		std::string Passwords::_getStringField(std::ifstream* inputFile, int64_t* lineNum);

		std::string _askForStringField(std::string fieldName);

		bool _doYouWantToUpdateField(std::string fieldName);

	public:
		Passwords(std::string fieldName);
		~Passwords();

		void getPassword();
		void deletePassword();
		void addPassword();
		void updatePassword();
};