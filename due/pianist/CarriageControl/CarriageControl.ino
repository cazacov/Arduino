#include "Carriage.h"

CarriageDriver car = CarriageDriver(3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600); 
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  car.Calibrate();

  while (true)  
  {
    Serial.println(car.GetPosition());
  }      
}
