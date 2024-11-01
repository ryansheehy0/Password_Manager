#include <cinttypes>
#include "../Include/ascii_keyboard_char.h"

// Private:---------------------------------------------------------------------

int8_t AsciiKeyboardChar::_hexToI4(char hex) {
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

int8_t AsciiKeyboardChar::_hexesToI8(char hex1, char hex2) {
	int8_t hex1I4 = _hexToI4(hex1);
	int8_t hex2I4 = _hexToI4(hex2);
	return (hex1I4 << 4) | hex2I4;
}

char AsciiKeyboardChar::_i8ToAsciiKeyboardChar(int8_t randomBits) {
	double randomNumFrom0To1 = randomBits / static_cast<double>(256);
	return randomNumFrom0To1 * (127 - 32) + 32;
}

// Public:----------------------------------------------------------------------

char AsciiKeyboardChar::hexesToAsciiKeyboardChar(char hex1, char hex2) {
	return _i8ToAsciiKeyboardChar(_hexesToI8(hex1, hex2));
}