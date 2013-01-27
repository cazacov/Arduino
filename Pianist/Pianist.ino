#include <Encoder.h>

//Arduino PWM Speed Contro
#define E1 5  
#define M1 4 
#define E2 6                      
#define M2 7

// Calibration sensor 
#define ST 8

// Encoders
#define ENC1 2
#define ENC2 3

#define EPSILON 10

char buf [20];

signed int motorSpeed = 0;
long pos = 0;
long oldPos = 0;


Encoder myEncoder(ENC1, ENC2);

void setup()
{
    Serial.begin(57600); 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);  
    pinMode(E1, OUTPUT);   
    pinMode(E2, OUTPUT);   
    pinMode(ST, INPUT);   
    pinMode(ENC1, INPUT);   
    pinMode(ENC2, INPUT);   
}

void loop()
{
  Serial.println("Hallo Welt!.");
  delay(3000);
  Serial.println("Calibrating...");
  delay(3000);
  Calibrate();
  Serial.println("Done.");
  
  pos = 0;
  
  while(true)
  {
    GoTo(1000);
    delay(500);
    pos = myEncoder.read();
    Serial.println(pos);

    GoTo(8000);
    delay(500);
    pos = myEncoder.read();
    Serial.println(pos);
  }
}

void GoTo(long pos)
{
  long myPos;
  do 
  {
    myPos = myEncoder.read();
    if (abs(myPos - pos) < EPSILON)
    {
      SetMotorSpeed(0);
    }
    else if (myPos < pos)
    {
      SetMotorSpeed(255);
    }
    else
    {
      SetMotorSpeed(-255);
    }
  }
  while (abs(myPos - pos) > EPSILON);

  SetMotorSpeed(0);
  sprintf(buf, "%ld %ld", pos, myPos);
  Serial.println(buf);
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
  myEncoder.write(0);
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

