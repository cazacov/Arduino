// 
// 
// 
#include "GraphSinus.h"
#include "OsciCanvas.h"

void GraphSinus::init()
{
	Canvas.init(-10, -1, 10, 1);

}

void GraphSinus::draw()
{
	for (double x = -10; x < 10; x+= 0.01)
	{
		double y = sin(x);
		Canvas.point(x, y);
	}
}
