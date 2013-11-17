// GraphSinus.h

#ifndef _GRAPHSINUS_h
#define _GRAPHSINUS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphSinus : public GraphBase
{
 private:


 public:
	virtual void init();
	virtual void draw();
};
#endif

