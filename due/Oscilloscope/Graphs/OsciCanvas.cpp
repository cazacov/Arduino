// 
// 
// 

#include "OsciCanvas.h"

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

void OsciCanvas::point(double x, double y)
{
	analogWrite(DAC0, x * scaleX + offsetX); 
	analogWrite(DAC1, y * scaleY + offsetY); 
	delayMicroseconds(DELAY);
}


OsciCanvas Canvas;

