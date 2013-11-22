// 
// 
// 
#include "GraphRadar.h"
#include "OsciCanvas.h"

void GraphRadar::init()
{
	Canvas.init(-10, -10, 10, 10);
}

void GraphRadar::draw()
{
	for (float t = 0; t  < PI*2; t+= 0.01)
	{
		float x = 10 * cos(t);
		float y = 10 * sin(t);
		Canvas.line(0,0, x, y);
		delay(5);
	}
}
