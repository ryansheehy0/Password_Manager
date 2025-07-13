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
		vector<Password> passwords;
		fstream file;
		string masterPassword;

	public:
		Passwords(fstream file, string masterPassword);

		void addPassword(string name, string username, string password);
		void updatePassword()
};