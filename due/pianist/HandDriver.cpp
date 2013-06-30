#include "HandDriver.h"

#define SERVODELAY 150

HandDriver::HandDriver()
{
  calibrationOffsets[0] = 70;
  calibrationOffsets[1] = -100;
  calibrationOffsets[2] = -50;
  calibrationOffsets[3] = -120;  
  calibrationOffsets[4] = 0;
	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		servos[i] = new Servo();
	}

}

void HandDriver::init(unsigned char noOfFirstPin)
{
	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		servos[i]->attach(noOfFirstPin + i);
		servos[i]->write(PosMiddle + calibrationOffsets[i]);
	}
}

void HandDriver::demo()
{
	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		setFinger(i, PosMiddle);
	}
	delay(SERVODELAY);

	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		setFinger(i, PosUp);
		delay(SERVODELAY);
	}
	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		setFinger(i, PosMiddle);
		delay(SERVODELAY);
	}

	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		setFinger(i, PosDown);
		delay(SERVODELAY);
	}
	for (unsigned char i = 0; i < SERVOCOUNT; i++)
	{
		setFinger(i, PosMiddle);
		delay(SERVODELAY);
	}
}

void HandDriver::setFinger(unsigned char fingerNo, FingerPosition position)
{
	servos[fingerNo]->write(position + calibrationOffsets[fingerNo]);
}

void HandDriver::fingerDown(uint8_t fingerNo)
{
  
}

void HandDriver::fingerUp(uint8_t fingerNo)
{
  
}

