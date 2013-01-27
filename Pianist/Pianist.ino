//Arduino PWM Speed Contro
short E1 = 5;  
short M1 = 4; 
short E2 = 6;                      
short M2 = 7;   

short ST = 8;

#include <PinChangeInt.h> // necessary otherwise we get undefined reference errors.
#include <AdaEncoder.h>

int8_t clicks=0;
long pos = 0;
char id=0;

char buf [20];

signed int motorSpeed = 0;

#include <Encoder.h>

Encoder encoder(10, 12);

void setup()
{
    Serial.begin(57600); 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);  
    pinMode(E1, OUTPUT);   
    pinMode(E2, OUTPUT);   
    pinMode(ST, INPUT);   
    
    AdaEncoder::addEncoder('a', 2, 3);
}

void loop()
{
  encoder *thisEncoder;
  Serial.println("Hallo Welt!.");
  delay(3000);
  Serial.println("Calibrating...");
  delay(3000);
  Calibrate();
  Serial.println("Done.");
  
  thisEncoder=AdaEncoder::genie(&clicks, &id);
  
  int oldPos = 0;
  while(true)
  {
    thisEncoder=AdaEncoder::genie(&clicks, &id);
    if (thisEncoder != NULL) {
      pos += clicks;
      if (clicks != 0)
      {
        Serial.println(pos);
      }
    }
  }    
    
    /*
    int i = digitalRead(Enc1);
    int j = digitalRead(Enc2);
    sprintf(buf, "%d %d", i, j);
    Serial.println(buf);
    */
   
   /* 
    int newPos = encoder.read();
    if (newPos != oldPos)
    {
      Serial.println(newPos);
      oldPos = newPos;
    }
    */
  }
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
  encoder.write(0);
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

