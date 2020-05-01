// Board.h

#ifndef _BOARD_h
#define _BOARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>


#define SIZE_X	10	
#define SIZE_Y	24	

#define CL_BLACK	0
#define CL_BLUE		1
#define CL_GREEN	2
#define CL_CYAN		3
#define CL_RED		4
#define CL_MAGENTA	5
#define CL_YELLOW	6
#define CL_WHITE	7

class Board240 
{
private:
	Adafruit_NeoPixel* pixels;
public:
	Board240(uint8_t pin);
	void dot(uint8_t x, uint8_t y, uint8_t color);
	void refresh();
	void digit(uint8_t n, uint8_t x, uint8_t y, uint8_t color);
};
#endif

