// 
// 
// 
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <avr/pgmspace.h>

#include "Board.h"

const uint8_t digits[] PROGMEM = { 
	0, 0x7C, 0x82, 0x82, 0x7C,		//	0
	0, 0x00, 0x84, 0xFE, 0x80,		//	1
	0, 0xE2, 0x92, 0x92, 0x9E,		//	2
	0, 0x92, 0x92, 0x92, 0x6C,		//	3
	0, 0x30, 0x28, 0x24, 0xFE,		//	4
	0, 0x9E, 0x92, 0x92, 0x62,		//	5
	0, 0xFE, 0x92, 0x92, 0xF2,		//	6
	0, 0x02, 0xC2, 0x22, 0x1E,		//	7
	0, 0xFE, 0x92, 0x92, 0xFE,		//	8
	0, 0x9E, 0x92, 0x92, 0xFE,		//	8
};


Board240::Board240(uint8_t pinNumber)
{
	this->pixels = new Adafruit_NeoPixel(SIZE_X * SIZE_Y, pinNumber, NEO_GRB + NEO_KHZ800);
	pixels->begin(); // This initializes the NeoPixel library.
	pixels->clear();
}

void Board240::dot(uint8_t x, uint8_t y, uint8_t color)
{
	x = 9 - x;
	int c = (x % 2) ? y : 23 - y;
	c += 24 * x;
	
	long lc = 0;
	if (color & 0x01)
	{
		lc |= 0x000000FF;
	}
	if (color & 0x02)
	{
		lc |= 0x0000FF00;
	}
	if (color & 0x04)
	{
		lc |= 0x00FF0000;
	}
	pixels->setPixelColor(c, lc);
}



void Board240::refresh()
{
	pixels->show();
}

void Board240::digit(uint8_t n, uint8_t x, uint8_t y, uint8_t color)
{
	for (uint8_t i = 0; i < 5; i++) {
		uint8_t d = pgm_read_byte_near(digits + n * 5 + i);
		for (uint8_t j = 0; j < 8; j++) {
			if (d & 0x01)
			{
				dot(x + i, y + j, color);
			}
			else {
				dot(x + i, y + j, CL_BLACK);
			}
			d >>= 1;
		}
	}

}
