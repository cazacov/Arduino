/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/
#define LASER 12
#define MOTOR 9

#define MAXSPEED 60
#define WORKSPEED 52


// Need the Servo library
#include <Servo.h>

// This is our motor.
Servo myMotor;

// Set everything up
void setup()
{
  // Put the motor to Arduino pin #9
  myMotor.attach(9);

  // Required for I/O from Serial monitor
  Serial.begin(57600);
  // Print a startup message
  Serial.println("initializing");
  pinMode(LASER, OUTPUT);
}

void loop()
{
  for (int i = 0; i < MAXSPEED; i++)
  {
    myMotor.write(i);
    Serial.println(i);
    delay(200);
  };
  delay(1000);
  for (int i = MAXSPEED; i > WORKSPEED; i--)
  {
    myMotor.write(i);
    Serial.println(i);
    delay(50);
   }
  while(1)
  {
    digitalWrite(LASER, HIGH);
    delayMicroseconds(200);
    digitalWrite(LASER, LOW);
    delayMicroseconds(200);
  }
}
