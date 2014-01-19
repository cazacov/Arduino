// 
// 
// 

#include "GraphSpiral.h"
#include "OsciCanvasInt.h"
#include "MathInt.h"

void GraphSpiral::init()
{
	CanvasInt.init(0,0);
	initialPhase = 0;

	for (int i = 0; i < 5; i++)
	{
		long phi = ((long)i << 13) / 5; // We are using integer trigonometry where 2Pi = 4096
		starCords[i][0] = (MathInt.sinInt(phi)) >> 3;
		starCords[i][1] = (MathInt.cosInt(phi)) >> 3;
	}
}

long initialPhase = 0;

void GraphSpiral::draw()
{
	for (long t = 0; t < 400; t++)
	{
		showTwoPoints(t, initialPhase);
	}
	showStar(250, 470, initialPhase);
	initialPhase += 12 ;
}

void GraphSpiral::showPoint(long t, long p)
{
	int x = (t * MathInt.sinInt((t << 5)  + p)) >> 9;
	int y0 = MathInt.cosInt((t << 5) + p);
	int y = (t * y0) >> 11;
	y = -t - y;
	CanvasInt.point(250 + x, 500 + y);
	int del = (y0 + 250) >> 3;
	delayMicroseconds(del);
}

void GraphSpiral::showTwoPoints(long t, long p)
{
	int x = (t * MathInt.sinInt((t << 5)  + p)) >> 9;
	int y = MathInt.cosInt((t << 5) + p);
	int y0 = (t * y) >> 11;
	int y1 = -y0 - t;
	int y2 = y0 - t;
	CanvasInt.point(250 + x, 450 + y1);
	int del = (y + 250) >> 3;
	delayMicroseconds(del);
	CanvasInt.point(250 - x, 450 + y2);
	del = (250 - y) >> 3;
	delayMicroseconds(del);
}

void GraphSpiral::showStar(int x0, int y0, long initialPhase)
{
	int x = starCords[0][0] + x0;
	int y = starCords[0][1] + y0;

	for (int i = 1; i <= 5; i++)
	{
		int index = i % 5;
		int x1 = starCords[index][0] * MathInt.cosInt(initialPhase) / 250 + x0;
		int y1 = starCords[index][1] + y0;
		CanvasInt.line(x, y, x1, y1);
		x = x1;
		y = y1;
	}
}
