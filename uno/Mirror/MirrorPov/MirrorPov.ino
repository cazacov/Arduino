/*
	Laser projector made from an old hard disk drive

	Author: Victor Cazacov
	License: MIT License
	
*/

// Third party libraries:
// PWMServo - controls a servo motor (in this case ESC) attached to PWM pin without using interrupts.
// http://arduiniana.org/libraries/pwmservo/// 
// Unpack it into Libraries folder of your Arduino IDE installation.

#include "Fonts.h"
#include "Laser.h"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MirrorController.h"
#include <PWMServo.h> 

#define LASER_PIN 2

MirrorController* mirrorController;
char buf[20];

char* message = " HELLO WORLD ";

void setup()
{
	Serial.begin(57600);
	Serial.println("Initializing...");
	mirrorController = new MirrorController();
	mirrorController->init();

	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, HIGH);
}

int correction[8] = { 17, 10, 0, 20, 45, 0, 0, -0 };  // time offset in microseconds to compensate non-ideal shape of mirrors
int lineOrder[8] = { 0, 7, 3, 4, 1, 6, 2, 5 };		// for better balance mirroring faces are not placed in strict incremental order		


void loop()
{
	delay(500);
	digitalWrite(LASER_PIN, LOW);

	unsigned char pbuf[5][20];

	for (int i = 0; i < 5; i++)
	{
		FONTS.getLine(message, i, pbuf[i]);
	}

	// re-arrange correction time offesets in the order of mirror faces
	byte ct[8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (lineOrder[j] == i)
			{
				ct[j] = correction[i];
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		correction[i] = ct[i];
	}


	Serial.println("Speeding up the mirror...");
	mirrorController->start();

	delay(3000);

	Serial.println("Measuring rotation speed...");
	long cycleTimeMs = mirrorController->calculateRotationSpeed();

	sprintf(buf, "Cycle time: %ld", cycleTimeMs);
	Serial.println(buf);

	long t0 = 170;
	long lineTime = cycleTimeMs >> 3;	// time in microseconds to draw one line
	long pixelTime = lineTime >> 7;		// time in microseconds to draw one pixel
	sprintf(buf, "Pixel time: %ld", pixelTime);
	Serial.println(buf);

	mirrorController->waitForBeginMarkFast();
	long prevStart = micros();
	delayMicroseconds(cycleTimeMs << 1);

	int pixels = strlen(message) * 8;
	long startTimes[8];

	do {
		mirrorController->waitForBeginMarkFast();
		long start = micros();
		long* sptr = startTimes;
		int* cptr = correction;
		long val = start + t0;
		
		for (int i = 0; i < 8; i++)
		{
			*sptr = val + (*cptr);
			sptr++;
			cptr++;
			val += lineTime;
		}
		
		sptr = startTimes;
		long t = *sptr;  // time in microseconds when to start drawing next pixel

		for (int i = 0; i < 8; i++)
		{
			int lineNr = lineOrder[i];
			unsigned char* ptr = pbuf[4 - lineNr];
			unsigned char bitMask = 0x80;
			unsigned char info = *ptr;

			if (lineNr < 5)
			{
				for (int p = 0; p < pixels; p++)
				{
					while (micros() < t)
					{
						// do nothing;
					}
					if (info & bitMask)
					{
						digitalWrite(LASER_PIN, HIGH);
					}
					else
					{
						digitalWrite(LASER_PIN, LOW);
					}
					bitMask >>= 1;
					if (bitMask == 0)
					{
						ptr++;
						info = *ptr;
						bitMask = 0x80;
						t += pixelTime;
					}
					t += pixelTime;
				}
			}
			digitalWrite(LASER_PIN, LOW);
			sptr++;
			t = *sptr;
		}
		lineTime = (start - prevStart) >> 3;
		pixelTime = lineTime >> 7;
		prevStart = start;
	} while (1);
}

