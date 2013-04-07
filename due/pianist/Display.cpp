#include "Display.h"
#include <stdarg.h>

MyDisplay::MyDisplay()
{
  lcd = new LiquidCrystal_I2C(0x27,16,2);
  lcd->init();
  lcd->backlight();
  lcd->print("Hello, world!");
}

void MyDisplay::Clear()
{
  lcd->clear();
}

void MyDisplay::Debug(char* message, ... )
{
  char buf[40];
  
  va_list argList;
  va_start(argList, message);
  vsprintf(buf, message, argList);
  va_end(argList);
  lcd->print(buf);
}

