#include "HandDriver.h"

#define SERVODELAY 150

HandDriver::HandDriver()
{
  servoPositions[0] = {800,1570,2400};
  servoPositions[1] = {800,1400,2000};
  servoPositions[2] = {800,1450,2000};  
  servoPositions[3] = {800,1380,2000};
  servoPositions[4] = {800,1500,2200};  
  
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
		servos[i]->write(servoPositions[i][PosMiddle]);
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
  servos[fingerNo]->write(servoPositions[fingerNo][position]);
}

void HandDriver::fingerDown(uint8_t fingerNo)
{
  
}

void HandDriver::fingerUp(uint8_t fingerNo)
{
  
}

