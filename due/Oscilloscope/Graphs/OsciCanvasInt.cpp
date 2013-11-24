// 
// 
// 

#include "OsciCanvasInt.h"
#define sign(x) ((x > 0)? 1 : ((x < 0)? -1: 0))

void OsciCanvasInt::init(int delPoint, int delLine)
{
	analogWriteResolution(9);  // set the analog output resolution to 12 bit (512 levels)
	delayPoint = delPoint;
	delayLine = delLine;
}

void OsciCanvasInt::point(int x, int y)
{
	if (x < 0 || x > 511)
	{
		return;
	}
	if (y < 0 || y > 511)
	{
		return;
	}
	analogWrite(DAC0, x); 
	analogWrite(DAC1, y); 
	delayMicroseconds(delayPoint);
}

// Generalized Bresenham's Line Drawing Algorithm
// See http://www.cs.umd.edu/class/fall2003/cmsc427/bresenham.html 
void OsciCanvasInt::line(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1); 
	int dy = abs(y2 - y1);
	int s1 = sign(x2 - x1); 
	int s2 = sign(y2 - y1);
	int x = x1; 
	int y = y1;
	int swap = 0;
	if (dy > dx) { 
		int temp = dx; 
		dx = dy; 
		dy = temp; 
		swap = 1;
	}
	int D = (dy << 1) - dx;
	for (int i = 0; i < dx; i++) 
	{
		analogWrite(DAC0, x); 
		analogWrite(DAC1, y); 
		while (D >= 0)
		{ 
			D = D - (dx << 1); 
			if (swap) 			{
				x += s1; 
			}
			else {
				y += s2; 
			}
		}
		D = D + (dy << 1); 
		if (swap) {
			y += s2;
		} else {
			x += s1;
		}
		if (delayLine)
		{
			delayMicroseconds(delayLine);
		}
	}	
}


OsciCanvasInt CanvasInt;

