#include "Carriage.h"

CarriageDriver car = CarriageDriver(3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600); 
  for (int i = 5; i >=0; i--)
  {
    Serial.println(i);
    delay(1000);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  car.Calibrate();
  delay(500);
  
  car.SpeedCheck();

  Serial.println("Done");
  while (true)  
  {
     ; //Serial.println(car.GetPosition());
  }      
}
