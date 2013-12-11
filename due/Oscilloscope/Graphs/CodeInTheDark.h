// CodeInTheDark.h

#ifndef _CODEINTHEDARK_h
#define _CODEINTHEDARK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GraphBase.h"

class CodeInTheDark : public GraphBase
{
 private:
	 void drawLines(int coordinates[][4], int length);
 public:
	virtual void init();
	virtual void draw();
};
#endif
