#include "OsciCanvasInt.h"
#include "GraphLissajous.h"

#define SCALEX  250
#define SCALEY  200

void GraphLissajous::init()
{
	CanvasInt.init(1,1);
}



float t = 0;

void GraphLissajous::draw()
{
	int x0 = 0, y0 = 0;

	do {
		int x = (int)(SCALEX * cos(3.0 * t)) + 256;
		int y = (int)(SCALEX * cos(4.01 * t)) + 256;
		t += 0.02;
		CanvasInt.line(x0, y0, x, y);
		x0 = x;
		y0 = y;
	} while(true);
}

