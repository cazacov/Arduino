// 
// 
// 

#include "GraphFlower.h"
#include "OsciCanvas.h"

void GraphFlower::init()
{
	Canvas.init(-1.5, -1.5, 1.5, 1.5);
}

void GraphFlower::draw()
{
	double max = PI * 2;
	double step = 0.001;

	for (double t = 0; t < max; t+=step)
	{
		double r = sin(7*t);
		Canvas.point(r * cos(t), r * sin(t));
		//delay(5);
	}
}
