/*
    Pianist - Arduino-controlled piano player made from an old inkjet printer.
    Author: Victor Cazacov
    Copyright (c) 2013

    This file is part of Pianist.

    Pianist is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pianist is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pianist.  If not, see <http://www.gnu.org/licenses/>.
*/    

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
  car.calibrate();
  
  car.goToPosition(7000);
  while (car.is_moving)
  {
    car.processEvents();
  }
  delay(100);
  int x = car.getPosition();
  
  car.goToPosition(2000);
  while (car.is_moving)
  {
    car.processEvents();
  }
  delay(100);
  int x2 = car.getPosition();
  
  dis.showLine(0, "X1=%d  X2=%d", x, x2);

  hand->demo();

  while(1);
}
