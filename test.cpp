#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::string fileName = "passwords.txt";

	// Open file
	std::ofstream outputFile(fileName);
	if (!outputFile) {
		std::cout << "Failed to open " << fileName << "\n";
		return 1;
	}
	outputFile << "Test1\n";
	outputFile << "Test2\n";
	outputFile << "Test3";
}