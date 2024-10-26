#include <cinttypes>
#include "keyboard_char.h"

int8_t KeyboardChar::_hexToI4(char hex) {
	int8_t i4;
	if (hex >= '0' && hex <= '9') {
		i4 = hex - '0';
	} else if (hex >= 'a' && hex <= 'f') {
		i4 = hex - 'a';
	} else {
		// Error. Not a hex value.
	}
	return i4;
}

int8_t KeyboardChar::_hexesToI8(char hex1, char hex2) {
	int8_t hex1I4 = _hexToI4(hex1);
	int8_t hex2I4 = _hexToI4(hex2);
	return (hex1I4 << 4) | hex2I4;
}

char KeyboardChar::_i8ToKeyboardChar(int8_t randomBits) {
	static int64_t index = 0;
	static int64_t start = 0;
	static int64_t end = (126 - 32);

	if (start == end) { // End of recursion
		return static_cast<char>(start + 32); // Converts the keyboard char back into ascii and returns
	}

	bool randomBit = (randomBits >> (7 - index)) & 1; // Gets the next random bit
	if (randomBit) { // Split the keyboard char space in half to the right
		start += (end - start + 1) / 2;
	} else { // Split the keyboard char space in half to the left
		end -= (end - start + 1) / 2;
	}

	index++;
	return _i8ToKeyboardChar(randomBits);
}

char KeyboardChar::hexesToKeyboardChar(char hex1, char hex2) {
	return _i8ToKeyboardChar(_hexesToI8(hex1, hex2));
}