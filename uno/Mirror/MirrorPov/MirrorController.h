// MirrorController.h

#ifndef _MIRRORCONTROLLER_h
#define _MIRRORCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Servo.h>

class MirrorController
{
 private:
	Servo* hddMotor;
 public:
	void init();
	void start();
	long waitForBeginMark();
	long calculateRotationSpeed();
};
#endif

