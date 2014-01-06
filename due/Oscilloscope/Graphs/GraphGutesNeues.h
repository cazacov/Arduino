// GraphGutesNeues.h

#ifndef _GRAPHGUTESNEUES_h
#define _GRAPHGUTESNEUES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphGutesNeues : public GraphBase
{
 private:
 public:
	void virtual init();
	void virtual draw();
};
#endif

