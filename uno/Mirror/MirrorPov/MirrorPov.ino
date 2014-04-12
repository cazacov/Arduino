#include "Fonts.h"
#include "Laser.h"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MirrorController.h"
#include <Servo.h>

#define LASER_PIN 2

MirrorController* mirrorController;
char buf[20];

char* message = "  HELLO WORLD";

void setup()
{
	Serial.begin(57600);
	Serial.println("Initializing...");
	mirrorController = new MirrorController();
	mirrorController->init();

	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, HIGH);
}

int correction[9] = { -35, -15, -25, -5, 0, 62, -5, -10 };
int lineOrder[8] = { 0, 7, 3, 4, 1, 6, 2, 5 };


void loop()
{
	delay(500);
	digitalWrite(LASER_PIN, LOW);

	unsigned char pbuf[5][20];
	char cb[10];

	for (int i = 0; i < 5; i++)
	{
		FONTS.getLine(message, i, pbuf[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		Serial.println(i);
		for (int j = 0; j < 11; j++)
		{
			sprintf(cb, "%X", pbuf[i][j]);
			Serial.println(cb);
		}
	}


	Serial.println("Speeding up the mirror...");
	mirrorController->start();

	delay(3000);

	Serial.println("Measuring rotation speed...");
	long cycleTimeMs = mirrorController->calculateRotationSpeed();

	sprintf(buf, "Cycle time: %ld", cycleTimeMs);
	Serial.println(buf);

	long t0 = 150;
	long lineTime = cycleTimeMs >> 3;
	long pixelTime = lineTime >> 7;
	sprintf(buf, "Pixel time: %ld", pixelTime);
	Serial.println(buf);

	long prevStart = mirrorController->waitForBeginMark();
	delayMicroseconds(cycleTimeMs << 1);

	int pixels = strlen(message) * 8;

	do {
		long start = mirrorController->waitForBeginMark();
		long t = start + t0;
		long lastCorrection = 0;
		t += correction[0];

		for (int i = 1; i <= 8; i++)
		{
			int lineNr = lineOrder[i - 1];
			unsigned char* ptr = pbuf[4 - lineNr];
			unsigned char bitMask = 0x80;
			char isOn = 1;

			for (int p = 0; p < pixels; p++)
			{
				while (micros() < t)
				{
					// do nothing;
				}
				if (lineNr < 5)
				{
					if ((*ptr) & bitMask)
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
						bitMask = 0x80;
					}
				}
				else
				{
					digitalWrite(LASER_PIN, LOW);
				}
				t += pixelTime;
			}
			digitalWrite(LASER_PIN, LOW);
			int nextCorrection = correction[lineOrder[i]];
			t += lineTime - pixels * pixelTime - lastCorrection + nextCorrection;
			lastCorrection = nextCorrection;
		}
		lineTime = (start - prevStart) >> 3;
		pixelTime = lineTime >> 7;
		prevStart = start;
	} while (1);
}

