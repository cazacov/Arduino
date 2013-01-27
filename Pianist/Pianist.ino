//Arduino PWM Speed Contro
short E1 = 5;  
short M1 = 4; 
short E2 = 6;                      
short M2 = 7;   

short ST = 2;

signed int motorSpeed = 0;

#include <Wire.h>

void setup()
{
    Serial.begin(57600); 
    Wire.begin();
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);  
    pinMode(E1, OUTPUT);   
    pinMode(E2, OUTPUT);   
    pinMode(ST, INPUT);   
}

void loop()
{
  Serial.println("Hallo Welt!.");
  delay(3000);
  Serial.println("Calibrating...");
  delay(3000);
  Calibrate();
  Serial.println("Done.");
  while(true);
}

void Calibrate()
{
  for (short i = 0; i < 3; i++)
  {
  Serial.println("Going left...");
  if (digitalRead(ST) == HIGH)
  {
    SetMotorSpeed(-255);
    while(digitalRead(ST) == HIGH)
    {
      ;
    }
    SetMotorSpeed(0);
  }
  Serial.println("Going right...");  
  SetMotorSpeed(200);
  while(digitalRead(ST) == LOW)
  {
    ;
  }
  }
  SetMotorSpeed(0);
}
  
 
void SetMotorSpeed(signed int motorSpeed)
{
  if (motorSpeed < 0)
  {
    digitalWrite(M1, HIGH);
  }
  else
  {
    digitalWrite(M1, LOW);
  }  
  
  int ms = abs(motorSpeed);
  if (ms > 255)
  {
    ms = 255;
  }
  analogWrite(E1, ms);  
}

