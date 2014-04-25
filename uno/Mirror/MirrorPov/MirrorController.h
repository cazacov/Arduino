// MirrorController.h

#ifndef _MIRRORCONTROLLER_h
#define _MIRRORCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <PWMServo.h>

class MirrorController
{
 private:
	 PWMServo* hddMotor;
 public:
	void init();
	void start();
	//long waitForBeginMark();
	void waitForBeginMarkFast();
	long calculateRotationSpeed();
};
#endif

