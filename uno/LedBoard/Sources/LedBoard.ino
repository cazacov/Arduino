// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "Board.h"
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <avr/pgmspace.h>

Board240 board(6);

void setup() {
}


void loop() {

	for (uint8_t c = 1; c < 8; c++)
	{
		for (long i = 0; i < 1000000L; i++)
		{
			long d = i;
			board.digit(d % 10, 5, 16, c);
			d /= 10;
			board.digit(d % 10, 0, 16, c);
			d /= 10;
			board.digit(d % 10, 5, 8, c);
			d /= 10;
			board.digit(d % 10, 0, 8, c);
			d /= 10;
			board.digit(d % 10, 5, 0, c);
			d /= 10;
			board.digit(d % 10, 0, 0, c);
			d /= 10;
			board.refresh();
		}
	}
}



