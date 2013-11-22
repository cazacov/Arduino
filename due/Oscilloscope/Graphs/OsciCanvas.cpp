// 
// 
// 
#include "OsciCanvas.h"
#define sign(x) ((x > 0)? 1 : ((x < 0)? -1: 0))

OsciCanvas::OsciCanvas()
{
	this->DELAY = 50;
}

void OsciCanvas::init(int minX, int minY, int maxX, int maxY)
{
	analogWriteResolution(12);  // set the analog output resolution to 12 bit (4096 levels)
	this->scaleX = 4096.0 / (maxX - minX);
	this->scaleY = 4096.0 / (maxY - minY);
	this->offsetX = -minX * scaleX;
	this->offsetY = -minY * scaleY;
}

void OsciCanvas::point(float x, float y)
{
	analogWrite(DAC0, x * scaleX + offsetX); 
	analogWrite(DAC1, y * scaleY + offsetY); 
	delayMicroseconds(DELAY);
}

void OsciCanvas::line(float fx1, float fy1, float fx2, float fy2)
{
	int x1 = fx1 * scaleX + offsetX;
	int x2 = fx2 * scaleX + offsetX;
	int y1 = fy1 * scaleY + offsetY;
	int y2 = fy2 * scaleY + offsetY;
	x1 >>= 2;
	x2 >>= 2;
	y1 >>= 2;
	y2 >>= 2;

	int x = x1; 
	int y = y1;
	int dx = abs(x2 - x1); 
	int dy = abs(y2 - y1);
	int s1 = sign(x2 - x1); 
	int s2 = sign(y2 - y1);
	int swap = 0;
	if (dy > dx) { 
		int temp = dx; 
		dx = dy; 
		dy = temp; 
		swap = 1;
	}
	int D = 2*dy - dx;
	for (int i = 0; i < dx; i++) 
	{
		analogWrite(DAC0, x << 2); 
		analogWrite(DAC1, y << 2); 
		while (D >= 0)
		{ 
			D = D - 2*dx; 
			if (swap) 			{
				x += s1; 
			}
			else {
				y += s2; 
			}
		}
		D = D + 2*dy; 
		if (swap) {
			y += s2;
		} else {
			x += s1;
		}
	}	
}

OsciCanvas Canvas;

