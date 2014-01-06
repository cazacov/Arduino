// GraphSpiral.h

#ifndef _GRAPHSPIRAL_h
#define _GRAPHSPIRAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphSpiral : public GraphBase
{
 private:
 public:
	void init();
	void draw();
};
#endif

