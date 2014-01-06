#include "OsciCanvasInt.h"
#include "GraphLissajousInt.h"

int sinArray[1025];

void GraphLissajousInt::init()
{
	CanvasInt.init(1,1);

	for (int i = 0; i <= 1024; i++)
	{
		sinArray[i] = sin(i * PI / (1024.0 * 2)) * 250;
	}
}

int sinInt(long t)
{
	if (t < 0)
	{
		return -sinInt(-t);
	}
	
	t = t & 0x00000FFF; // 2Pi = 4096
	if (t <= 1024)
	{
		return sinArray[t];
	}
	else if (t <= 2048)
	{
		return sinArray[2048 - t];
	}
	else if (t <= 3072)
	{
		return -sinArray[t - 2048];
	}
	else return -sinArray[4096 - t];
}


int cosInt(long t)
{
	if (t < 0)
	{
		return cosInt(-t);
	}
	return sinInt(t + 1024);
}


void GraphLissajousInt::draw()
{
	int x0 = 0, y0 = 0;
	long t = 0;

	do {
		int x = cosInt(3 * t) + 256;
		int y = sinInt((4097 * t) >> 10) + 256;
		t += 32;
		CanvasInt.line(x0, y0, x, y);
		x0 = x;
		y0 = y;
	} while(t < 2000000);
}

