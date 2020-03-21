#pragma once
#include <Arduino.h>


class MotorController
{
private:
	uint8_t switchPin;
	long stepNr;
public:
	MotorController(uint8_t switchPin);
	void calibrate();
	void gotoMm(int posMm);
	int posMm();
	void dong();
	void start();
	void stop();
};

