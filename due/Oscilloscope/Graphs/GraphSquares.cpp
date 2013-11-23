// 
// 
// 
#include "GraphSquares.h"
#include "OsciCanvasInt.h"

void GraphSquares::init()
{
	CanvasInt.init();
}

void GraphSquares::draw()
{
	int points[4][2] = {{0,0}, {511,0}, {511, 511}, {0, 511}};
	int newPoints[4][2];

	for (int i = 0; i < 40; i++)
	{
		for(int k = 0; k < 10; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				int e = (j+1) % 4;
				CanvasInt.line(points[j][0], points[j][1], points[e][0], points[e][1]);
			}
		}

		for (int j = 0; j < 4; j++)
		{
			int e = (j+1) % 4;
			newPoints[j][0] = points[j][0] +  ((points[e][0] - points[j][0]) >> 3);
			newPoints[j][1] = points[j][1] +  ((points[e][1] - points[j][1]) >> 3);
		}
		for (int j = 0; j < 4; j++)
		{
			points[j][0] = newPoints[j][0];
			points[j][1] = newPoints[j][1];
		}
	}
}


