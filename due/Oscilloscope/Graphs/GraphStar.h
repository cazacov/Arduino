// GraphStar.h

#ifndef _GRAPHSTAR_h
#define _GRAPHSTAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphStar : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

