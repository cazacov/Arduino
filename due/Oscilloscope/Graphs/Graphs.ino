#include "GraphRadar.h"
#include "GraphFlower.h"
#include "GraphSinus.h"
#include "GraphBase.h"
#include "OsciCanvas.h"

//GraphBase* graph = new GraphSinus(); 
//GraphBase* graph = new GraphFlower(); 
GraphBase* graph = new GraphRadar(); 

void setup()
{
	graph->init();	
}


void loop()
{
	graph->draw();
}

