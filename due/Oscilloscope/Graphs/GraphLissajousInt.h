// GraphLissajousInt.h

#ifndef _GRAPHLISSAJOUSINT_h
#define _GRAPHLISSAJOUSINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphLissajousInt : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

