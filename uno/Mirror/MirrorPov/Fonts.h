// Fonts.h

#ifndef _FONTS_h
#define _FONTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Fonts
{
 private:
 public:
	void init();
	void getLine(char* text, int lineNr, unsigned char* cbuf);
};
extern Fonts FONTS;
#endif

