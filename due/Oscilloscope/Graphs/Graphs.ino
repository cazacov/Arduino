#include "GraphHelloHabr.h"
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
	new GraphHallo(),
	new GraphFlower(),
	new GraphSquares(),
	new GraphLissajousInt(),
	new GraphGutesNeues(),
	new GraphChristmasTree(),
	new GraphSpiral(),
	new Graph2014(),
	new GraphFireworks(),
	new GraphFireworks()
};

int weights[] = { 15, 12, 10, 9, 8, 7, 4};

//GraphHelloHabr gh;

void setup()
{
	Serial.begin(115200);
	MathInt.init();
	randomSeed(analogRead(0));
	//gh.init();
}

int graphIndex = 0;

void loop()
{
	//gh.draw();
	//return;

	GraphBase* graph;

	/*int sum = 0;
	for (int i = 0; i < sizeof(weights) / sizeof(weights[0]); i++)
	{
		sum += weights[i];
	}

	int r = random(sum);

	
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
*/
	graph = graphs[graphIndex];
	graph->init();

	long stopTime = millis() + 10*1000;  // Max 10 seconds execution time

	do {
		graph->draw();
	}
	while (millis() < stopTime);
	graphIndex++;
	graphIndex %= 10;
}

