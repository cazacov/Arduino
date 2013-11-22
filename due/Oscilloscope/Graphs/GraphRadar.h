// GraphRadar.h

#ifndef _GRAPHRADAR_h
#define _GRAPHRADAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphRadar : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

