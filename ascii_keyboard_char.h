#pragma once

#include <cinttypes>

/*
An ascii keyboard character is an ascii value from 32-126.
This includes all the characters you can type on the keyboard besides the tab key.
*/

class AsciiKeyboardChar {
	private:
		static int8_t _hexToI4(char hex);
		static int8_t _hexesToI8(char hex1, char hex2);
		static char _i8ToAsciiKeyboardChar(int8_t randomBits);
	public:
		static char hexesToAsciiKeyboardChar(char hex1, char hex2);
};