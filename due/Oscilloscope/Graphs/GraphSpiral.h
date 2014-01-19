// GraphSpiral.h

#ifndef _GRAPHSPIRAL_h
#define _GRAPHSPIRAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class GraphSpiral : public GraphBase
{
 private:
	short starCords[5][2];

	long initialPhase;
	void showPoint(long t, long p);
	void showTwoPoints(long t, long p);
	void showStar(int x0, int y0, long initialPhase);
 public:
	void init();
	void draw();
};
#endif

