#include "GraphFlower.h"
#include "GraphSinus.h"
#include "GraphBase.h"
#include "OsciCanvas.h"

//GraphBase* graph = new GraphSinus(); 
GraphBase* graph = new GraphFlower(); 

void setup()
{
	graph->init();	
}


void loop()
{
	graph->draw();
}

