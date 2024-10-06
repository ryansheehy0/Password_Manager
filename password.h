#pragma once

#include <cstdint>
#include <string>

struct Password {
	int64_t id;
	std::string name;
	std::string username;
	std::string password;
};