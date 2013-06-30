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

//#include "C:/Programme/Arduino/hardware/tools/avr/avr/include/avr/io.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ps2.h>
#include <Servo.h>


#include "Display.h"
#include "Carriage.h"
#include "PhysicalModel.h"
#include "HandDriver.h"
#include "melody.h"
#include "SongBook.h"

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
  car.calibrate();  
  
  Melody melody;
  
  melody.init(MySongBook.HappyBirthday);
                
                
  char b[30];
  
  long delayAfterNote  = 200L * 1000;
  
  melody.start();
  Serial.println("started");
  delay(100);
  while(!melody.isFinished())
  {
    int pos = melody.getHandPosition();
    int len = melody.getNoteLength();
    sprintf(b, "Next pos=%d\t len=%d", pos, len);
    Serial.println(b);
    
    long startTime = micros() + delayAfterNote;
    car.goToPosition(pos);
    while(car.is_moving)
    {
      ;
    }
    while (micros() < startTime)
    {  
      ;
    }
    
    hand->setFinger(4, PosDown);
    delay(len);
    hand->setFinger(4, PosMiddle);
    delay(100);
    
    int cPos = car.getPosition();
    Serial.println(cPos);
    melody.nextNote();
  }
  
  while(1);
}
