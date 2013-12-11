// GraphChristmasTree.h

#ifndef _GRAPHCHRISTMASTREE_h
#define _GRAPHCHRISTMASTREE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphChristmasTree : public GraphBase
{
 private:
 public:
	virtual void init();
	virtual void draw();
};
#endif

