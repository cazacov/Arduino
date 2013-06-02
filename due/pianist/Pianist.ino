/*
    Pianist - Arduino-controlled piano player made from an old inkjet printer.
    Author: Victor Cazacov
    Copyright (c) 2013
    
    ####################################################################

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
    
    #####################################################################
    
    Third-party libraries that must be installed into Arduino libraries folder
    - LiquidCrystal I2C
      Driver for I2C/TWI LCD1602 Module 
      http://www.dfrobot.com/wiki/index.php?title=I2C/TWI_LCD1602_Module_(SKU:_DFR0063)
      
    Changes in libraries:
      
    Servo.h (Arduino\hardware\arduino\sam\libraries\Servo\Servo.h)
      Do NOT DEFINE _useTimer3, _useTimer4, _useTimer5 because we are going to use 
      DUE timer TC5 in Carriage driver.    
*/    

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ps2.h>
#include <Servo.h>


#include "Display.h"
#include "Carriage.h"
#include "PhysicalModel.h"
#include "HandDriver.h"
#include "melody.h"

DebugDisplay dis;
PS2Mouse mouse(3, 2);

CarriageDriver car = CarriageDriver(3);
HandDriver* hand = new HandDriver();

void setup() {
  Serial.begin(57600); 
  dis.begin();
  hand->init(8);
}

void loop() 
{
  Melody melody;
  
  melody.init(  "G4 G4 A4 G4 C5 B5+"
                "G4 G4 A4 G4 D5 C5+"
                "G4 G4 G5 E4 C5 C5 B4 A4+"
                "F5 F5 E5 C5 D5 C5");
  
  car.calibrate();
  
  car.goToPosition(7000);
  delay(500); 
  int x1 = car.getPosition();
  
  car.goToPosition(2000);
  delay(500);
  int x2 = car.getPosition();
  
  dis.showLine(0, "T1=%d  T2=%d", 7000, 2000);
  dis.showLine(1, "X1=%d  X2=%d", x1, x2);

  hand->demo();
  
  melody.start();
  
  while (!melody.isFinished())
  {
    int pos = melody.getHandPosition();
    car.goToPosition(pos);
    while(car.is_moving)
      ;
    int noteLength = melody.getNoteLength();
    int fingerNo = melody.getActiveFinger();
    hand->fingerDown(fingerNo);
    delay(noteLength);
    hand->fingerUp(fingerNo);
    melody.nextNote();
  }    

  while(1);
}
