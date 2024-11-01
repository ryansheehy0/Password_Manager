#pragma once

#include <cstdint>
#include <string>

class Password {
	private:
		int64_t _id;
		std::string _name;
		std::string _encryptedName;
		std::string _username;
		std::string _encryptedUsername;
		std::string _password;
		std::string _encryptedPassword;
		std::string _masterPassword;

		std::string _encrypt(std::string fieldName, std::string fieldValue);
		std::string _decrypt(std::string fieldName, std::string encryptedFieldValue);

		std::string _simpleEncryption(std::string value1, std::string value2);
		std::string _simpleDecryption(std::string encryptedValue1, std::string encryptedValue2);

		std::string _sha512(const std::string& input);
		std::string _hash(std::string input);

	public:
		Password(bool encryptedInput, int64_t id, std::string name, std::string username, std::string password, std::string masterPassword);

		void print() const;

		void updateName(std::string newName);
		void updateUsername(std::string newUsername);
		void updatePassword(std::string newPassword);

		int64_t id() const {return _id;}
		std::string name() const {return _name;}
		std::string encryptedName() const {return _encryptedName;}
		std::string username() const {return _username;}
		std::string encryptedUsername() const {return _encryptedUsername;}
		std::string password() const {return _password;}
		std::string encryptedPassword() const {return _encryptedPassword;}
};