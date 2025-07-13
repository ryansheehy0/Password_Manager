#pragma once

#include <string>

using std::string;

enum class ArgType {
	ENCRYPTED,
	DECRYPTED
};

class Password {
	private:
		int _id;
		string _masterPassword;

		string _name;
		string _username;
		string _password;
		string _encryptedName;
		string _encryptedUsername;
		string _encryptedPassword;

	public:
		Password(string masterPassword, int id, ArgType argType,
			string name,
			string username,
			string password
		);

		// Getters
		int id() const {return _id;}
		string name() const {return _name;}
		string username() const {return _username;}
		string password() const {return _password;}
		string encryptedName() const {return _encryptedName;}
		string encryptedUsername() const {return _encryptedUsername;}
		string encryptedPassword() const {return _encryptedPassword;}

		// Setters
		void updateName(string newName);
		void updateUsername(string newUsername);
		void updatePassword(string newPassword);

		void print() const;

	private:
		string _encrypt(string fieldName, string value) const;
		string _decrypt(string fieldName, string value) const { return _encrypt(fieldName, value); };
		string _hash(string value) const;
		string _sha512(string value) const;
};