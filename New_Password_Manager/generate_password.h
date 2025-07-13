#pragma once

#include <string>

using std::string;

class GeneratePassword {
	public:
		static void generatePassword();

	private:
		static bool _doYouWantToInclude(string fieldName);
		static int _randomIndex(int length);
		static int _getPasswordLength();
};