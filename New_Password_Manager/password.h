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

		void print() const;
		void updateName(string newName);
		void updateUsername(string newUsername);
		void updatePassword(string newPassword);

		// Getters
		int id() const {return _id;}
		string name() const {return _name;}
		string username() const {return _username;}
		string password() const {return _password;}
		string encryptedName() const {return _encryptedName;}
		string encryptedUsername() const {return _encryptedUsername;}
		string encryptedPassword() const {return _encryptedPassword;}

	private:
		string encrypt(string value) const;
		string decrypt(string value) const;
		string hash(string value) const;
};