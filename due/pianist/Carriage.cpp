#include "Carriage.h"
#include "Logger.h"

//http://arduino.cc/forum/index.php/topic,140205.0.html
// Uses pins 2 and 13 for reading quadrature encoders

// Uses HAL sensor on pin 3 (or specified by endSensorPinNr parameter in constructor)
// to detect most right position

// Uses DFRobot L298P shield to control motor (pins 4,5,6,7)

CarriageDriver::CarriageDriver(unsigned char endSensorPinNr)
{
  endSensorPin = endSensorPinNr;
  quad_A = 2;
  quad_B = 13;
  motorDirectionPin = 4;
  motorSpeedPin = 5;
  
  mask_quad_A = digitalPinToBitMask(quad_A);
  mask_quad_B = digitalPinToBitMask(quad_B);  
  
  pinMode(motorDirectionPin, OUTPUT);   
  pinMode(motorSpeedPin, OUTPUT);   
  pinMode(endSensorPin, INPUT);   
  
  // activate peripheral functions for quad pins
  REG_PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_A;   // choose peripheral option B    
  REG_PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
  REG_PIOB_ABSR |= mask_quad_B;   // choose peripheral option B 
    
  // activate clock for TC0
  REG_PMC_PCER0 = (1<<27);
  // select XC0 as clock source and set capture mode
  REG_TC0_CMR0 = 5; 
  // activate quadrature encoder and position measure mode, no filters
  REG_TC0_BMR = (1<<9)|(1<<8)|(1<<12);
  // enable the clock (CLKEN=1) and reset the counter (SWTRG=1) 
  // SWTRG = 1 necessary to start the clock!!
  REG_TC0_CCR0 = 5;    
  SetMotorSpeed(0);
}

long CarriageDriver::GetPosition()
{
  long result = REG_TC0_CV0;
  return -result;
}  
  
void CarriageDriver::Calibrate()
{
  for (short i = 0; i < 3; i++)
  {
    Serial.println("Going left...");
    if (!IsAtTheEnd())
    {
      SetMotorSpeed(-200);
      while(!IsAtTheEnd())
      {
        ;
      }
      SetMotorSpeed(0);
    }
    Serial.println("Going right...");  
    SetMotorSpeed(200);
    while(IsAtTheEnd())
    {
      ;
    }
  }
  SetMotorSpeed(0); 
  delay(300);
  ResetPosition();
}

void CarriageDriver::GoRaw(int newPosition)
{
  do 
  {
    int delta = newPosition - GetPosition();
    if (abs(delta) < 30)
    {
      SetMotorSpeed(0);
      return;
    }
    else
    {
      SetMotorSpeed(delta);  
    }
  } while (true);
}

void CarriageDriver::ResetPosition()
{
  REG_TC0_CCR0 = 5;     
}

boolean CarriageDriver::IsAtTheEnd()
{
  return digitalRead(endSensorPin) == LOW;
}

void CarriageDriver::SetMotorSpeed(int newSpeed)
{
  if (newSpeed < 0)
  {
    digitalWrite(motorDirectionPin, HIGH);
  }
  else
  {
    digitalWrite(motorDirectionPin, LOW);
  }  
  
  int ms = abs(newSpeed);
  if (ms > 255)
  {
    ms = 255;
  }
  analogWrite(motorSpeedPin, ms);     
}

void CarriageDriver::SpeedCheck2(PhysicalModel* pm)
{
  Logger lg;
  lg.Clear();
  
  int motorSpeed;
  int prevPos = GetPosition();
  int counter = 0;
  int phase = 0;
  long nxtTime;
  
  while (counter < 500)
  {
    nxtTime = micros() + 1000;
    long curPos = GetPosition();  
    
    switch (phase)
    {
      case 0: // acceleration
        motorSpeed = 250;
        if (curPos >= 7000)
        {
          motorSpeed = -220;
          phase = 1;
        }
        break;
      case 1: // deceleration
        motorSpeed = -220;
        if (curPos <= prevPos)
        {
          motorSpeed = 0;
          phase = 2;
        }
        break;     
      case 2: // idle
        motorSpeed = 0;
        break;             
    }        
    prevPos = curPos;
    SetMotorSpeed(motorSpeed);
    lg.AddToLog(curPos, motorSpeed);
    counter++;
    while (micros() < nxtTime)
    {
      ;
    }
  }
  SetMotorSpeed(0);
  lg.FlushToSerial();
  pm->InitAcc(7000, -220, &lg);
}


void CarriageDriver::MoveABit()
{
  int pos = GetPosition();
  SetMotorSpeed(200);
  
  do {
    ;
  } while (abs(pos - GetPosition()) < 2);
  SetMotorSpeed(0);
}



void CarriageDriver::GoExact(int targetPosition, PhysicalModel* pm)
{
  pm->ShowEstimations();
  
  Logger logger;
  logger.Clear();
  
  int motorSpeed;
  int prevPos = GetPosition();
  long nxtTime;
  int counter = 0;
  int stopFlag = 0;
  MovingPhase movingPhase = mpAcceleration;

  while (counter < 400)
  {
    nxtTime = micros() + 1000;
    int curPos = GetPosition();  
    int curSpeed = curPos - prevPos;
    int delta = targetPosition - curPos;
    
    if (delta >= 0)
    {
      motorSpeed = pm->CalculateMotorSpeed(delta, curSpeed, movingPhase);
    }
    else
    {
      motorSpeed = -pm->CalculateMotorSpeed(-delta, -curSpeed, movingPhase);
    }
    
    if (movingPhase == mpStop)
    {
      Serial.println("STOP");
      SetMotorSpeed(0);
      break;
    }
    
    // some checks
    if (curPos > 7500)
    {
      Serial.println("7500 Limit");
      SetMotorSpeed(0);
      break;
    }
    if (curPos < 500 && motorSpeed < 0)
    {
      Serial.println("500 Limit");
      SetMotorSpeed(0);
      break;
    }
    
    prevPos = curPos;
    SetMotorSpeed(motorSpeed);
    logger.AddToLog(curPos, motorSpeed, pm->LastEstimation);
    counter++;
    while (micros() < nxtTime)
    {
      ;
    }
  }
  SetMotorSpeed(0);
  logger.FlushToSerial();
}  


