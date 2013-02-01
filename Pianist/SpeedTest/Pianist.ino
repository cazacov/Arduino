#include <Encoder.h>

//Arduino PWM Speed Contro
#define E1 5  
#define M1 4 
#define E2 6                      
#define M2 7

#define DATASIZE 500

int bigdata[DATASIZE];
//int bigtime[DATASIZE];

// Calibration sensor 
#define ST 8

// Encoders
#define ENC1 2
#define ENC2 3

#define EPSILON 10

char buf [20];

int initPos = 0;
int curPos = 0;
int stopPos = 0;

long initTime;
long curTime;
long nxtTime;



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
  
  GoTo(1000);
  delay(500);
  GoTo(1000);
  delay(500);
  GoTo(1000);
  delay(500);
  GoTo(1000);
  delay(1000);
  
  initPos = myEncoder.read();
  stopPos = initPos + 7000; 
  Serial.println(initPos);
  delay(500);
  
  int idx = 0;
  SetMotorSpeed(250);    
  unsigned int isRunning = 1;
  
  initTime = micros();
  
  while(true)
  {
    curTime = micros();
    curPos = myEncoder.read();
    
    if (isRunning && (curPos > stopPos))
    {
        SetMotorSpeed(0);    
        isRunning = 0;
    }
    int deltaX = curPos - initPos;
    int deltaT = (curTime - initTime) / 100;
    bigdata[idx] = isRunning << 15 | deltaX;
//    bigtime[idx] = deltaT;
    
    idx++;
    if (idx >= DATASIZE)
    {
      break;
    }
    
    nxtTime = curTime + 1000;
    
    while (micros() < nxtTime)
    {
      ;
    }
  }
  
  Serial.println("Finished");
  
  for (int i = 0; i < DATASIZE; i++)
  {
    isRunning = (bigdata[i] & 0x8000) ? 1 : 0;
    sprintf(buf, "%d\t%d\t%d", i, isRunning, (bigdata[i] & 0x7FFF)),
    Serial.println(buf);
  }
  
  Serial.println("Done");
  
  while(true);
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

