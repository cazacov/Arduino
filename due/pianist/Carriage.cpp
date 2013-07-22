#include "Carriage.h"
#include "Logger.h"


//http://arduino.cc/forum/index.php/topic,140205.0.html
// Uses pins 2 and 13 for reading quadrature encoders

// Uses HAL sensor on pin 3 (or specified by endSensorPinNr parameter in constructor)
// to detect most right position

// Uses DFRobot L298P shield to control motor (pins 4,5,6,7)

CarriageDriver* carriageInstance;
Logger logg;

void setupTimer();  

CarriageDriver::CarriageDriver(unsigned char endSensorPinNr) 
{
  is_moving = 0;
  targetPosition = 0;
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
  setMotorSpeed(0);
  
  carriageInstance = this;
}

long CarriageDriver::getPosition()
{
  long result = REG_TC0_CV0;
  return -result;
}  
  
void CarriageDriver::calibrate()
{
  for (short i = 0; i < 3; i++)
  {
    Serial.println("Going left...");
    if (!isAtTheEnd())
    {
      setMotorSpeed(-MEDIUM_MOTOR_POWER);
      while(!isAtTheEnd())
      {
        ;
      }
      setMotorSpeed(0);
    }
    Serial.println("Going right...");  
    setMotorSpeed(MEDIUM_MOTOR_POWER);
    while(isAtTheEnd())
    {
      ;
    }
  }
  setMotorSpeed(0); 
  delay(250);
  resetPosition();
  moveABit();
  delay(50);
  speedCheck(DIR_FORWARD);
  delay(100);
  speedCheck(DIR_BACK);
  delay(100);
  setupTimer();  
}

void CarriageDriver::resetPosition()
{
  REG_TC0_CCR0 = 5;     
}

boolean CarriageDriver::isAtTheEnd()
{
  return digitalRead(endSensorPin) == LOW;
}

void CarriageDriver::setMotorSpeed(int newSpeed)
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

void CarriageDriver::speedCheck(int8_t moveDirection)
{
  Logger lg;
  lg.clear();
  
  int motorSpeed;
  int prevPos = getPosition();
  int counter = 0;
  int phase = 0;
  long nxtTime;
  
  while (counter < LOGSIZE)
  {
    nxtTime = micros() + PROCESSING_CYCLE;
    long curPos = getPosition();  
    
    switch (phase)
    {
      case 0: // acceleration
        motorSpeed = moveDirection > 0 ? FULL_MOTOR_POWER : -FULL_MOTOR_POWER;
        if (moveDirection > 0 && curPos >= 7000 || moveDirection < 0 && curPos <= 1000)
        {
          motorSpeed = -MEDIUM_MOTOR_POWER * moveDirection;
          phase = 1;
        }
        break;
      case 1: // deceleration
        motorSpeed = moveDirection > 0 ? -MEDIUM_MOTOR_POWER : MEDIUM_MOTOR_POWER;
        if (moveDirection > 0 && curPos <= prevPos
            || moveDirection < 0 && curPos >= prevPos)
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
    setMotorSpeed(motorSpeed);
    lg.addToLog(curPos, motorSpeed);
    counter++;
    while (micros() < nxtTime)
    {
      ;
    }
  }
  setMotorSpeed(0);
  pm.calculateBrakingDistance(&lg, moveDirection);
}


void CarriageDriver::moveABit()
{
  int pos = getPosition();
  setMotorSpeed(MEDIUM_MOTOR_POWER);
  
  do {
    ;
  } while (abs(pos - getPosition()) < 2);
  setMotorSpeed(0);
}



void CarriageDriver::goToPosition(int newPosition)
{
  logg.clear();
  is_moving = 0;  
  setMotorSpeed(0);
  targetPosition = newPosition;
  prevPos = getPosition();
  moveDirection = targetPosition > prevPos ? DIR_FORWARD : DIR_BACK;
  movingPhase = mpAcceleration;
  
  nxtTime = micros() - 10;
  is_moving = 1;
  
  //processEvents();
}

int CarriageDriver::getPosMm()
{
  return getPosition() * 1000 / TICKS_PER_METER;  
}  

void CarriageDriver::goToPosMm(int newPositionMm)
{
  long pos = newPositionMm;

  if (pos < LIMIT_LEFT)
  {
    pos = LIMIT_LEFT;
  }
  
  if (pos > LIMIT_RIGHT)
  {
    pos = LIMIT_RIGHT;
  }
  
  pos = pos * TICKS_PER_METER / 1000;
  goToPosition(pos);
}

void CarriageDriver::processEvents()
{
  if (!is_moving) return;
  
  long currentTime = micros();
  
  if (currentTime < nxtTime) return;

  nxtTime = currentTime + 1000;
  
  int curPos = getPosition();  
  int delta = targetPosition - curPos;
  
  int motorSpeed;    
  if (delta >= 0)
  {
    motorSpeed = pm.calculateMotorSpeed(delta, curPos - prevPos, movingPhase, moveDirection);
  }
  else
  {
    motorSpeed = -pm.calculateMotorSpeed(-delta, prevPos - curPos, movingPhase, moveDirection);
  }
  
  logg.addToLog(curPos, curPos - prevPos, motorSpeed);
  
  // some checks
  if (motorSpeed > 0 && curPos > 8200)
  {
    Serial.println("8200 Limit");
    movingPhase = mpStop;
  }
  
  if (motorSpeed < 0 && curPos < 0)
  {
    Serial.println("0 Limit");
    movingPhase = mpStop;
  }

  if (movingPhase == mpStop)
  {
    Serial.println("STOP");
    Serial.println(motorSpeed);
    Serial.println(curPos);
    Serial.println(delta);
    setMotorSpeed(0);
    is_moving = 0;
    //logg.flushToSerial();
    return;
  }
    
  prevPos = curPos;
  setMotorSpeed(motorSpeed);
}  

uint8_t bestClock(uint32_t frequency, uint32_t& retRC){
	/*
	    Timer		Definition
	    TIMER_CLOCK1	MCK/2
	    TIMER_CLOCK2	MCK/8
	    TIMER_CLOCK3	MCK/32
	    TIMER_CLOCK4	MCK/128
	*/
	struct {
		uint8_t flag;
		uint8_t divisor;
	} clockConfig[] = {
		{ TC_CMR_TCCLKS_TIMER_CLOCK1, 2 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK2, 8 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK3, 32 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK4, 128 }
	};
	float ticks;
	float error;
	int clkId = 3;
	int bestClock = 3;
	float bestError = 1.0;
	do 
	{
		ticks = (float) VARIANT_MCK / (float) frequency / (float) clockConfig[clkId].divisor;
		error = abs(ticks - round(ticks));
		if (abs(error) < bestError) 
		{
			bestClock = clkId;
			bestError = error;
		}
	} while (clkId-- > 0);
	ticks = (float) VARIANT_MCK / (float) frequency / (float) clockConfig[bestClock].divisor;
	retRC = (uint32_t) round(ticks);
	return clockConfig[bestClock].flag;
}

// Osciloscope on pin 50 can be used to check timer execution.

int ledPin = 50;                 // LED connected to digital pin 13
int ledState = 0; 

void setupTimer()
{
  Tc *tc = TC1;
  uint32_t channel = 2;
  IRQn_Type irq = TC5_IRQn;
  uint32_t frequency = 1000;
  
  pinMode(ledPin, OUTPUT);
  
  uint32_t rc = 0;
  uint8_t clock;

  // Yes, we don't want pmc protected!
  pmc_set_writeprotect(false);

  // Enable clock for the timer
  pmc_enable_periph_clk((uint32_t)irq);

  // Do magic, and find's best clock
  clock = bestClock(frequency, rc);
  Serial.println("Clock");
  Serial.println(clock);
  
  Serial.println("RC");
  Serial.println(rc);

  TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | clock);
    
  TC_SetRA(tc, channel, rc/2); //50% high, 50% low
  TC_SetRC(tc, channel, rc);
  TC_Start(tc, channel);
  tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;  
  NVIC_EnableIRQ(irq);
}

void TC5_Handler(){
  TC_GetStatus(TC1, 2);
  digitalWrite(ledPin, ledState = 1 - ledState);
  carriageInstance->processEvents();
}

