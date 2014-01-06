// 
// 
// 

#include "Graph2014.h"
#include "OsciCanvasInt.h"

void Graph2014::init()
{
	CanvasInt.init(0,0);

	x = 0;
	y = 0;

	vx = (2 + random(3)) / 200.0;
	vy = (5 + random(5)) / 200.0;
}

void Graph2014::draw()
{
	int year2014[][4] =
	{
		{1,11,	4,11},	// 2
		{4,11,	4,8},
		{4,8,	1,5},
		{1,5,	4,5},

		{5,5,	5,11},	// 0
		{5,11,	8,11},
		{8,11,	8,5},
		{8,5,	5,5},
		{5,5,	8,11},

		{9,9,	10,11},	// 1
		{10,11,	10,5},
		{9,5,	11,5},

		{14,5,	14,11},	// 4
		{14,11,	12,7},
		{12,7,	15,7}
	};

	for (int i = 0; i < sizeof(year2014) / sizeof(year2014[0]); i++)
	{
		CanvasInt.line(
			(year2014[i][0] << 5) + x,
			(year2014[i][1] << 5) + y,
			(year2014[i][2] << 5) + x,
			(year2014[i][3] << 5) + y);

		x += vx;
		y += vy;

		if (x < -31)
		{
			x = -31;
			vx = -vx;
		}
		if (x > 31)
		{
			x = 31;
			vx = -vx;
		}

		if (y < -150)
		{
			y = -150;
			vy = -vy;
		}

		if (y > 150)
		{
			y = 150;
			vy = -vy;
		}
	}
}

