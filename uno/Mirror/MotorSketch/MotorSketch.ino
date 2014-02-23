/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

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
}

void loop()
{
  for (int i = 90; i < 180; i++)
  {
    myMotor.write(i);
    Serial.println(i);
    delay(200);
  };
  for (int i = 180; i > 90; i--)
  {
    myMotor.write(i);
    Serial.println(i);
    delay(50);
   }

}
