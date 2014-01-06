// Graph2014.h

#ifndef _GRAPH2014_h
#define _GRAPH2014_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class Graph2014 : public GraphBase
{
 private:
	float x;
	float y;
	float vx;
	float vy;
 public:
	void virtual init();
	void virtual draw();
};
#endif

