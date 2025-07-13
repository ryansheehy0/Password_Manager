#include "password.h"

// Constructor -----------------------------------------------------------------
Password::Password(string masterPassword, ArgType argType, int id, string name, string username, string password) {
	_masterPassword = masterPassword;
	_id = id;
	switch (argType) {
		case ArgType::ENCRYPTED:
			_name = decrypt(name);
			_username = decrypt(username);
			_password = decrypt(password);
			_encryptedName = name;
			_encryptedUsername = username;
			_encryptedPassword = password;
			break;
		case ArgType::DECRYPTED:
			_name = name;
			_username = username;
			_password = password;
			_encryptedName = encrypt(name);
			_encryptedUsername = encrypt(username);
			_encryptedPassword = encrypt(password);
			break;
	}
}

// Public ----------------------------------------------------------------------
// Private ---------------------------------------------------------------------