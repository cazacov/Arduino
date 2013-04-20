#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ps2.h>
#include <Servo.h>

#include "Display.h"
#include "Carriage.h"
#include "PhysicalModel.h"
#include "HandDriver.h"

DebugDisplay dis;
PS2Mouse mouse(3, 2);

CarriageDriver car = CarriageDriver(3);
PhysicalModel* pm;
HandDriver* hand = new HandDriver();

void setup() {
  Serial.begin(57600); 
  dis.begin();
  pm = new PhysicalModel();
  hand->init(8);
}

void loop() 
{
  car.Calibrate();
  delay(500);
  car.SpeedCheck2();


  car.GoExact(2000);
  delay(100);
  int x = car.GetPosition();
  
  car.GoExact(7000);
  delay(100);
  int x2 = car.GetPosition();
  
  dis.showLine(0, "X1=%d  X2=%d", x, x2);

  hand->demo();

  while(1);
}
