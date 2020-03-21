// Piano.h
#ifndef _PIANO_h
#define _PIANO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MotorController.h"

class Piano
{
private:
	MotorController* motorController;
	int noteCoordinate(char* note);
public:
	Piano(MotorController* motorController);
	void play(char* melody);
};


#endif

