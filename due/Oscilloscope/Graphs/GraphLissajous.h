// GraphLissajous.h

#ifndef _GRAPHLISSAJOUS_h
#define _GRAPHLISSAJOUS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphLissajous : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

