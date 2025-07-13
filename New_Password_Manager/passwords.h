#pragma once

#include "password.h"
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::fstream;

class Passwords {
	private:
		fstream _file;
		string _masterPassword;
		vector<Password> _passwords;

	public:
		Passwords(fstream file, string masterPassword);

		void printPassword() const;
		void deletePassword();
		void addPassword();
		void updatePassword();

	private:
		int _askForPasswordIndex() const ;
		string _askForStringField(string fieldName) const;
		bool _doYouWantToUpdateField(string fieldName) const;
		void _writeToFile() const;
};