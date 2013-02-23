#include "Carriage.h"
#include "PhysicalModel.h"

CarriageDriver car = CarriageDriver(3);
PhysicalModel* pm;

void setup() {
  Serial.begin(57600); 
  for (int i = 5; i >=0; i--)
  {
    Serial.println(i);
    delay(800);
  }
  pm = new PhysicalModel();
}

void loop() 
{
  //return;
  
  car.Calibrate();
  delay(500);
  
  //car.SpeedCheck();
  
  car.SpeedCheck2(pm);
  
  car.GoRaw(2000);
  delay(1000);
  
  for (int i = 0; i < 1; i++)
  {  
    car.GoExact(7000, pm);
    delay(1000);
    Serial.println(car.GetPosition());
    
    car.GoExact(1000, pm);
    delay(1000);
    Serial.println(car.GetPosition());
  }

  while (true)  
  {
     ; //Serial.println(car.GetPosition());
  }      
}
