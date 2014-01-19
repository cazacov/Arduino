// TextWriter.h

#ifndef _TEXTWRITER_h
#define _TEXTWRITER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "OsciCanvasInt.h"

class TextWriter
{
 private:
	 void drawLetter(int x0, int y0, unsigned int coordinates[][4], int lineCount);
 public:
	 void A(int x0, int y0);
	 void B(int x0, int y0);
	 void E(int x0, int y0);
	 void G(int x0, int y0);
	 void H(int x0, int y0);
	 void J(int x0, int y0);
	 void L(int x0, int y0);
	 void N(int x0, int y0);
	 void O(int x0, int y0);
	 void R(int x0, int y0);
	 void S(int x0, int y0);
	 void T(int x0, int y0);
	 void U(int x0, int y0);
};
#endif

