// 
// 
// 
#include "CodeInTheDark.h"
#include "OsciCanvasInt.h"

int code[][4] =
{
	{8,23,	4,27}, //C
	{4,27,	8,31},
	
	{12,31,	14,27}, // O
	{14,27,	12,23},
	{12,23,	10,27},
	{10,27,	12,31},

	{18,31,	22,27}, // D
	{22,27,	18,23},
	{18,23,	18,31},

	{24,31,	28,31}, //E
	{24,27,	28,27},
	{24,23,	28,23}
};	

int inThe[][4] =
{
	{2,20,	20,20}, // -

	{8,14,	8,18}, // I
	
	{10,14,	10,18}, // N
	{10,18,	12,14},
	{12,14,	12,18},

	{16,18,	18,18}, // T
	{17,18,	17,14},

	{20,14,	20,18}, // H
	{20,16,	22,16},
	{22,14,	22,18},

	{26,18,	24,18}, // E
	{24,18,	24,14},
	{24,14,	26,14},
	{26,16,	24,16},
	
	{12,12,	30,12}, // -
};	

int dark[][4] =
{
	{4,10,	8,6}, //D
	{8,6,	4,2},
	{4,2,	4,10},
	
	{10,2,	12,10}, // A
	{12,10,	14,2},
	
	{18,2,	18,10}, // R
	{18,10,	20,8},
	{20,8,	18,6},
	{18,6,	22,2},

	{24,2,	24,10}, //K
	{28,10,	24,6},
	{24,6,	28,2}
};	



void CodeInTheDark::init()
{
	CanvasInt.init(1,1000);
}

void CodeInTheDark::draw()
{
	int del = 2000;

	for (int i = 0; i < 200; i++)
	{
		CanvasInt.init(1, del);
		drawLines(code, sizeof(code) / sizeof(code[0]));
		drawLines(inThe, sizeof(inThe) / sizeof(inThe[0]));
		drawLines(dark, sizeof(dark) / sizeof(dark[0]));
		del = del * 8 / 10;
	}
}

void CodeInTheDark::drawLines(int coordinates[][4], int length)
{
	for (int i = 0; i < length; i++)
	{
		CanvasInt.line(
			coordinates[i][0] << 4,
			coordinates[i][1] << 4,
			coordinates[i][2] << 4,
			coordinates[i][3] << 4);
	} 
}
