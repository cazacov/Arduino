// GraphFlower.h

#ifndef _GRAPHFLOWER_h
#define _GRAPHFLOWER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "GraphBase.h"

class GraphFlower : public GraphBase
{
 private:
 public:
	void init();
	void draw();
};
#endif

