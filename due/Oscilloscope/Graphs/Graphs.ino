#include "MathInt.h"
#include "Graph2014.h"
#include "GraphFireworks.h"
#include "TextWriter.h"
#include "GraphGutesNeues.h"
#include "GraphSpiral.h"
#include "GraphLissajousInt.h"
#include "GraphLissajous.h"
#include "GraphText.h"
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
#include "GraphHallo.h"
#include "OsciCanvas.h"


GraphBase* graphs[] = {
	new GraphFireworks(),
	new Graph2014(),
	new GraphGutesNeues(),
	new GraphChristmasTree(),
	new GraphLissajousInt(),
	new GraphFlower(),
	new GraphHallo()
};

int weights[] = { 15, 12, 10, 9, 8, 7, 4};

GraphLissajousInt gh;

void setup()
{
	Serial.begin(115200);
	MathInt.init();
	randomSeed(analogRead(0));
	gh.init();
}


void loop()
{
	gh.draw();
	return;

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

	long stopTime = millis() + 12*1000;  // Max 12 seconds execution time

	do {
		graph->draw();
	}
	while (millis() < stopTime);
}

