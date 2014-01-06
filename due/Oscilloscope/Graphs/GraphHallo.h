// GraphHallo.h

#ifndef _GRAPHHALLO_h
#define _GRAPHHALLO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphHallo : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

