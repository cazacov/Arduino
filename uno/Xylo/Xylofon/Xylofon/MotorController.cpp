#include "Arduino.h"
#include "MotorController.h"

#define MOTORX_DIR_PIN 3
#define MOTORX_STEP_PIN 2
#define HAMMER_PIN 12
#define ENABLE_PIN 13

MotorController::MotorController(uint8_t switchPin)
{
	pinMode(ENABLE_PIN, OUTPUT);
	digitalWrite(ENABLE_PIN, HIGH);
	pinMode(HAMMER_PIN, OUTPUT);
	digitalWrite(HAMMER_PIN, LOW);
	this->switchPin = switchPin;
	pinMode(switchPin, INPUT_PULLUP);
	pinMode(MOTORX_DIR_PIN, OUTPUT);
	pinMode(MOTORX_STEP_PIN, OUTPUT);
	digitalWrite(MOTORX_DIR_PIN, LOW);
	digitalWrite(MOTORX_STEP_PIN, HIGH);
}

void MotorController::calibrate()
{
	start();
	digitalWrite(MOTORX_DIR_PIN, LOW);
	while (digitalRead(switchPin))
	{
		digitalWrite(MOTORX_STEP_PIN, HIGH);
		delayMicroseconds(100);
		digitalWrite(MOTORX_STEP_PIN, LOW);
		delayMicroseconds(1000);
	}
	stepNr = 0;
	delay(200);
	stop();
}

void MotorController::gotoMm(int posMm)
{
	long target = (long)posMm * 10L;

	if (target > stepNr)
	{
		digitalWrite(MOTORX_DIR_PIN, HIGH);
		while (stepNr < target)
		{
			digitalWrite(MOTORX_STEP_PIN, HIGH);
			delayMicroseconds(100);
			digitalWrite(MOTORX_STEP_PIN, LOW);
			delayMicroseconds(500);
			stepNr++;
		}
	}
	else 
	{
		digitalWrite(MOTORX_DIR_PIN, LOW);
		while (target < stepNr)
		{
			digitalWrite(MOTORX_STEP_PIN, HIGH);
			delayMicroseconds(100);
			digitalWrite(MOTORX_STEP_PIN, LOW);
			delayMicroseconds(500);
			stepNr--;
		}
	}
}

int MotorController::posMm()
{
	return stepNr / 10L;
}

void MotorController::dong() {
	digitalWrite(HAMMER_PIN, HIGH);
	delay(11);
	digitalWrite(HAMMER_PIN, LOW);
}

void MotorController::start()
{
	digitalWrite(ENABLE_PIN, LOW);
}

void MotorController::stop()
{
	digitalWrite(ENABLE_PIN, HIGH);
}