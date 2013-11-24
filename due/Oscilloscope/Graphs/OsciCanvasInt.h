// OsciCanvasInt.h

#ifndef _OSCICANVASINT_h
#define _OSCICANVASINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class OsciCanvasInt
{
 private:
	int delayPoint;
	int delayLine;
 public:
	static const int SizeX = 512;
	static const int SizeY = 512;
	void init(int delPoint = 10, int delLine = 0);
	void point(int x, int y);
	void line(int x1, int y1, int x2, int y2);
};

extern OsciCanvasInt CanvasInt;

#endif

