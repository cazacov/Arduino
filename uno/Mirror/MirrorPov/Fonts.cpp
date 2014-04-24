// 
// 
// 
#include "Fonts.h"
#include "Arduino.h"
#include <avr/pgmspace.h>

prog_uchar font5x8[130] PROGMEM = {
	// A
	0, 0, 0, 0, 0,
	// B
	0, 0, 0, 0, 0,
	// C
	0, 0, 0, 0, 0,
	// D
	0xF8, 0xC6, 0xC6, 0xC6, 0xF8,
	// E
	0xFC, 0xC0, 0xFC, 0xC0, 0xFC,
	// F
	0, 0, 0, 0, 0,
	// G
	0, 0, 0, 0, 0,
	// H
	0xCC, 0xCC, 0xFC, 0xCC, 0xCC,
	// I
	0x70, 0x20, 0x20, 0x20, 0x70,
	// J
	0, 0, 0, 0, 0,
	// K
	0xCC, 0xD8, 0xF0, 0xD8, 0xCC,
	// L
	0xC0, 0xC0, 0xC0, 0xC0, 0xFC,
	// M
	0, 0, 0, 0, 0,
	// N
	0, 0, 0, 0, 0,
	// O
	0x78, 0x84, 0x84, 0x84, 0x78,
	// P
	0, 0, 0, 0, 0,
	// Q
	0, 0, 0, 0, 0,
	// R
	0xF0, 0x88, 0xF0, 0x88, 0x84,
	// S
	0, 0, 0, 0, 0,
	// T
	0, 0, 0, 0, 0,
	// U
	0xCC, 0xCC, 0xCC, 0xCC, 0x78,
	// V
	0, 0, 0, 0, 0,
	// W
	0x92, 0x92, 0x92, 0x92, 0x7C,
	// X
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	// Y
	0, 0, 0, 0, 0,
	// Z
	0xF8, 0x10, 0x20, 0x40, 0xF8
};

void Fonts::init()
{
	

}

void Fonts::getLine(char* text, int lineNr, unsigned char* cbuf)
{
	int len = strlen(text);

	for (int i = 0; i < len; i++)
	{
                if (text[i] == ' ')
                {
                  cbuf[i] = 0;
                }
                 else {
		int addr = (text[i] - 'A') * 5 + lineNr;
		unsigned char pbyte = pgm_read_byte_near(font5x8 + addr);
		cbuf[i] = pbyte;  
                }
	}
}
Fonts FONTS;

