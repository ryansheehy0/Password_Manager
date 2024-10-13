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

		Password();
		Password(int64_t id, std::string name, std::string username, std::string password, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword) : _id(id), _name(name), _username(username), _password(password), _encryptedName(encryptedName), _encryptedUsername(encryptedUsername), _encryptedPassword(encryptedPassword) {}

		std::string _encrypt(std::string fieldName, std::string value);
		std::string _decrypt(std::string fieldName, std::string encryptedValue);

		std::string _hash(std::string value);

		std::string _simpleEncryption(std::string value1, std::string value2);
		std::string _simpleDecryption(std::string value1, std::string value2);

	public:
		static Password* createFromPassword(int64_t id, std::string name, std::string username, std::string password);
		static Password* createFromEncryptedPassword(int64_t id, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword);

		void print();

		void updateName(std::string name);
		void updateUsername(std::string username);
		void updatePassword(std::string password);

		std::string name();
		int64_t id();
};