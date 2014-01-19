// GraphHelloHabr.h

#ifndef _GRAPHHELLOHABR_h
#define _GRAPHHELLOHABR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphHelloHabr : public GraphBase
{
 private:
 public:
	void virtual init();
	void virtual draw();
};
#endif

