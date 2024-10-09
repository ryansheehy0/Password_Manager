#include "password.h"

Password::Password(int64_t id, std::string name, std::string username, std::string password)
: _id(id), _name(name), _username(username), _password(password) {}

void Password::print() {
	std::cout << "Name    : " << _name << "\n";
	std::cout << "Username: " << _name << "\n";
	std::cout << "Password: " << _name << "\n";
}

void Password::update(int64_t id, std::string name, std::string username, std::string password) {
	_id = id;
 _name = name;
 _username = username;
 _password = password;
}