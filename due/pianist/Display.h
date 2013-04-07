// Display.h
#ifndef _DISPLAY_h
#define _DISPLAY_h

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class MyDisplay
{
  private:
    LiquidCrystal_I2C* lcd;
  public:    
    MyDisplay();
    void Clear();
    void Debug(char* message, ...);
};

#endif
