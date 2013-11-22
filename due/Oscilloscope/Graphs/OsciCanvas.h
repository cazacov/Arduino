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
	 float scaleX;
	 float scaleY;
	 int offsetX;
	 int offsetY; 
	 int DELAY;
 public:
	OsciCanvas();
	void init(int minX, int minY, int maxX, int maxY);
	void point(float x, float y);
	void line(float x1, float y1, float x2, float y2);
};

extern OsciCanvas Canvas;

#endif

