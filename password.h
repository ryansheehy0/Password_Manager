#pragma once

#include <cstdint>
#include <string>

class Password {
	private:
		int64_t _id;
		std::string _name;
		std::string _username;
		std::string _password;

		Password();

	public:
		Password(int64_t id, std::string name, std::string username, std::string password);

		void print();

		void update(int64_t id, std::string name, std::string username, std::string password);
};