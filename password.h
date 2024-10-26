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

		Password();
		Password(int64_t id, std::string name, std::string username, std::string password, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword, std::string masterPassword);

		static std::string _encrypt(std::string fieldName, std::string fieldValue, std::string masterPassword, int64_t id);
		static std::string _decrypt(std::string fieldName, std::string encryptedFieldValue, std::string masterPassword, int64_t id);

		static std::string _simpleEncryption(std::string value1, std::string value2);
		static std::string Password::_simpleDecryption(std::string encryptedValue1, std::string encryptedValue2);

		static std::string _sha512(const std::string& input);
		static std::string _hash(std::string input);

	public:
		static Password* createFromPassword(int64_t id, std::string name, std::string username, std::string password);
		static Password* createFromEncryptedPassword(int64_t id, std::string encryptedName, std::string encryptedUsername, std::string encryptedPassword);

		void print() const;

		void updateName(std::string name);
		void updateUsername(std::string username);
		void updatePassword(std::string password);

		std::string name() const {return _name;};
		int64_t id() const {return _id;};
};