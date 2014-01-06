// GraphFireworks.h

#ifndef _GRAPHFIREWORKS_h
#define _GRAPHFIREWORKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphFireworks : public GraphBase
{
 private:
 public:
	void virtual init();
	void virtual draw();
};
#endif

