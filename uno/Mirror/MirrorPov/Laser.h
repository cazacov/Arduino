// laser.h

#ifndef _LASER_h
#define _LASER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Laser
{
 private:


 public:
	void init();
	void On();
	void Off();
};
#endif

