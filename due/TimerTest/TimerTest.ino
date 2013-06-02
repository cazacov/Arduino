#include <Servo.h>

int ledPin = 50;                 // LED connected to digital pin 13
int ledState = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(57600);
  setupTimer();
}

void loop() {
  while (1);
  
  digitalWrite(ledPin, ledState = 1 - ledState);
  delay(20);
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


void setupTimer()
{
  Tc *tc = TC1;
  uint32_t channel = 2;
  IRQn_Type irq = TC5_IRQn;
  uint32_t frequency = 1000;
  
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
}
