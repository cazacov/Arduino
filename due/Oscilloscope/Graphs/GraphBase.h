// GraphBase.h

#ifndef _GRAPHBASE_h
#define _GRAPHBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

