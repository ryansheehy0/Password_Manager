#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

char randomKeyboardCharReturnsAscii(bool randomBits[8]) {
	static int64_t index = 0;
	static int64_t start = 0;
	static int64_t end = (126-32);

	if (start == end) { // End of recursion
		return static_cast<char>(start + 32); // Converts the keyboard char back into ascii and returns
	}

	bool randomBit = randomBits[index];
	std::cout << "Start: " << start << " End: " << end << "\n";
	if (randomBit) { // Split the keyboard char space in half to the right
		start += (end - start + 1) / 2;
	} else { // Split the keyboard char space in half to the left
		end -= (end - start + 1) / 2;
	}

	index++;
	return randomKeyboardCharReturnsAscii(randomBits);
}

std::string _sha512(const std::string& str) {
		unsigned char hash[SHA512_DIGEST_LENGTH];
    // Directly use the SHA256 function to hash the input string
    SHA512(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

std::string _hash(std::string str) {
	const int64_t ROUNDS = 50;

	std::string repeatedSha512 = str;
	for(int64_t i = 0; i < ROUNDS; i++) {
		repeatedSha512 = _sha512(repeatedSha512);
	}

	// Convert the hexadecimal characters to arrays of bools.
}

int main() {
	//bool randomBits[] = {0, 1, 0, 1, 1, 1, 0, 0};
	//std::cout << randomKeyboardCharReturnsAscii(randomBits);
	std::cout << _sha512("test");
}