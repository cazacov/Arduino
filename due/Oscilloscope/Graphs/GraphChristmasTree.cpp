// 
// 
// 

#include "OsciCanvasInt.h"
#include "GraphChristmasTree.h"


int christmasTree[][2] =
{
	{8,	14},
	{10,12},
	{9,	12},
	{11,10},
	{9,	10},
	{12,7},
	{10,7},
	{14,3},
	{9,3},
	{9,1},
	{7,1},
	{7,3},
	{2,3},
	{6,7},
	{4,7},
	{7,10},
	{5,10},
	{7,12},
	{6,12},
	{8,14}
};



void GraphChristmasTree::init()
{
	CanvasInt.init(1,1500);
}

void GraphChristmasTree::draw()
{
	for (int i = 1; i < sizeof(christmasTree) / sizeof(christmasTree[0]); i++)
	{
		CanvasInt.line(
			christmasTree[i-1][0] << 5,
			christmasTree[i-1][1] << 5,
			christmasTree[i][0] << 5,
			christmasTree[i][1] << 5);
	}
}

