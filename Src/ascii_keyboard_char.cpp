#include <cinttypes>
#include "../Include/ascii_keyboard_char.h"

// Private:---------------------------------------------------------------------

uint8_t AsciiKeyboardChar::_hexToU4(char hex) {
	uint8_t u4;
	if (hex >= '0' && hex <= '9') {
		u4 = hex - '0';
	} else if (hex >= 'a' && hex <= 'f') {
		u4 = hex - 'a' + 10;
	} else {
		// Error. Not a hex value.
	}
	return u4;
}

uint8_t AsciiKeyboardChar::_hexesToU8(char hex1, char hex2) {
	uint8_t hex1U4 = _hexToU4(hex1);
	uint8_t hex2U4 = _hexToU4(hex2);
	return (hex1U4 << 4) | hex2U4;
}

char AsciiKeyboardChar::_u8ToAsciiKeyboardChar(uint8_t randomBits) {
	double randomNumFrom0To1 = randomBits / static_cast<double>(256);
	return randomNumFrom0To1 * (127 - 32) + 32;
}

// Public:----------------------------------------------------------------------

char AsciiKeyboardChar::hexesToAsciiKeyboardChar(char hex1, char hex2) {
	return _u8ToAsciiKeyboardChar(_hexesToU8(hex1, hex2));
}