// 
// 
// 
#include "GraphStar.h"
#include "OsciCanvasInt.h"

void GraphStar::init()
{
	CanvasInt.init(0, 200); // delay 200 microseconds on drawing lines
}

void GraphStar::draw()
{
	for (int i = 0; i < 20; i++)
	{
		CanvasInt.line(128,32, 256, 480 );
		CanvasInt.line(256,480, 384,32 );
		CanvasInt.line(384,32, 32,320 );
		CanvasInt.line(32,320, 480,320 );
		CanvasInt.line(480,320, 128,32 );
	}
}




