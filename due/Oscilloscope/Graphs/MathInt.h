// MathInt.h

#ifndef _MATHINT_h
#define _MATHINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class TMathInt
{
 private:
	 unsigned short sinArray[1025];
 public:
	void init();
	int sinInt(long t);
	int cosInt(long t);
};

extern TMathInt MathInt;

#endif

