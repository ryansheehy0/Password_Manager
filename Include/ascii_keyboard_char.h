#pragma once

#include <cinttypes>

/*
An ascii keyboard character is an ascii value from 32-126.
This includes all the characters you can type on the keyboard besides the tab key.
*/

class AsciiKeyboardChar {
	private:
		static uint8_t _hexToU4(char hex);
		static uint8_t _hexesToU8(char hex1, char hex2);
		static char _u8ToAsciiKeyboardChar(uint8_t randomBits);
	public:
		static char hexesToAsciiKeyboardChar(char hex1, char hex2);
};