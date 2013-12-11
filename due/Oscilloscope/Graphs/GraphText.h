// GraphText.h

#ifndef _GRAPHTEXT_h
#define _GRAPHTEXT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphText : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif


