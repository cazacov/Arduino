#include "OsciCanvasInt.h"
#include "GraphLissajousInt.h"
#include "MathInt.h"

void GraphLissajousInt::init()
{
	CanvasInt.init(1,1);
}



void GraphLissajousInt::draw()
{
	int x0 = 0, y0 = 0;
	long t = 0;

	do {
		int x = MathInt.cosInt(3 * t) + 256;
		int y = MathInt.sinInt((4097 * t) >> 10) + 256;
		t += 32;
		CanvasInt.line(x0, y0, x, y);
		x0 = x;
		y0 = y;
	} while(t < 2000000);
}

