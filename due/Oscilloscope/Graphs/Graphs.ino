#include "GraphChristmasTree.h"
#include "CodeInTheDark.h"
#include "GraphText.h"
#include "Anna.h"
#include "GraphStar.h"
#include "GraphSquares.h"
#include "OsciCanvasInt.h"
#include "GraphRadar.h"
#include "GraphFlower.h"
#include "GraphSinus.h"
#include "GraphBase.h"
#include "GraphText.h"
#include "CodeInTheDark.h"
#include "GraphChristmasTree.h"
#include "OsciCanvas.h"


GraphBase* graphs[] = {
	new CodeInTheDark(),
	new GraphChristmasTree(),
	new GraphSquares(),
	new GraphRadar(),
	new GraphFlower(),
	new GraphStar(),
};

int weights[] = { 15, 4, 3, 2, 2, 1};

void setup()
{
	
}


void loop()
{
	int sum = 0;
	for (int i = 0; i < sizeof(weights) / sizeof(weights[0]); i++)
	{
		sum += weights[i];
	}

	int r = random(sum);

	GraphBase* graph;
	sum = 0;
	for (int i = 0; i < sizeof(weights) / sizeof(weights[0]); i++)
	{
		sum += weights[i];
		if (sum > r)
		{ 
			graph = graphs[i];
			break;
		}
	}

	graph->init();

	long stopTime = millis() + 15*1000;  // Max 20 seconds execution time

	do {
		graph->draw();
	}
	while (millis() < stopTime);
}

