#include "Laser.h"
#include <Arduino.h>

#define LASER_PIN	2

void Laser::init()
{
	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, LOW);
	Serial.println("Laser initialized");
	digitalWrite(LASER_PIN, HIGH);
}

void Laser::On()
{
	digitalWrite(LASER_PIN, HIGH);
}

void Laser::Off()
{
	digitalWrite(LASER_PIN, LOW);
}


