// 
// 
// 
#include "GraphText.h"
#include "OsciCanvasInt.h"

int koordinaten[12][4] =
{
	{1,11,	3,15},
	{3,15,	5,11},
	{2,13,	4,13},
	{6,11,	6,15},
	{6,13,	8,13},
	{8,15,	8,11},
	{9,11,	9,15},
	{9,13,	11,13},
	{11,15,	11,11},
	{12,11,	14,15},
	{14,15,	16,11},
	{15,13,	13,13}
};	

void Namenschreiber(int startY);

void GraphText::init()
{
	CanvasInt.init(1,1);
}

void GraphText::draw()
{
	int startY;

	startY = -350;
	do {
		Namenschreiber(startY);
		startY = startY + 1;
	} while (startY < 30);

	startY = 30;
	do {
		Namenschreiber(startY);
		startY = startY - 1;
	} while (startY > -350);
}

void Namenschreiber(int startY)
{
	int LN	= 0;

	do {
		CanvasInt.line(
			koordinaten[LN][0]*32,
			koordinaten[LN][1]*32 + startY,
			koordinaten[LN][2]*32,
			koordinaten[LN][3]*32 + startY);
		LN = LN + 1;
	} while (LN < 12);
}
