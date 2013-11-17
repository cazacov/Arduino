// OsciCanvas.h

#ifndef _OSCICANVAS_h
#define _OSCICANVAS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class OsciCanvas
{
 private:
	 double scaleX;
	 double scaleY;
	 int offsetX;
	 int offsetY; 
	 int DELAY;
 public:
	OsciCanvas();
	void init(int minX, int minY, int maxX, int maxY);
	void point(double x, double y);
};

extern OsciCanvas Canvas;

#endif

