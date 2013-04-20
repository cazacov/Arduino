// Display.h
#ifndef _DEBUGDISPLAY_h
#define _DEBUGDISPLAY_h

#define MAXROWS 2
#define MAXCOLUMNS 16

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class DebugDisplay
{
  private:
    char dispChars[MAXROWS][MAXCOLUMNS];
    LiquidCrystal_I2C* lcdDisplay;
    int x, y;
    void rawPrint(char* text);
    void scrollUp();    
    void print(char* message, ...);    
    void println(char* message, ...);
    char lastLen[2];
  public:    
    DebugDisplay();
    void begin();
    void clear();
    void showLine(int row, char* message, ...);    
};
#endif
