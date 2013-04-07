#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ps2.h>
#include "Carriage.h"
#include "PhysicalModel.h"
#include "HandDriver.h"
#include "Display.h"


CarriageDriver car = CarriageDriver(3);
PhysicalModel* pm;
HandDriver* hand = new HandDriver();
PS2Mouse mouse(3, 2);
MyDisplay dis;

void setup() {
  Serial.begin(57600); 
  for (int i = 5; i >=0; i--)
  {
    dis.Debug("%d%", i);
    Serial.println(i);
    delay(800);
  }
  pm = new PhysicalModel();
  hand->init(8);
}

void loop() 
{
  //return;
  
  car.Calibrate();
  delay(500);
  
  hand->demo();

  while(1);
  
  //car.SpeedCheck();
  
  car.SpeedCheck2(pm);
  
  car.GoRaw(2000);
  delay(1000);
  
  while(1);
  
  
  
  
}
