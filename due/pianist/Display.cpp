#include "Display.h"
#include <stdarg.h>

DebugDisplay::DebugDisplay()
{
  lcdDisplay = new LiquidCrystal_I2C(0x27,16,2);
}

void DebugDisplay::begin()
{
  x = y = 0;
  lastLen[0] = lastLen[1] = 16;
  for (char i = 0; i < MAXROWS; i++)
  {
    for (char j = 0; j < MAXCOLUMNS; j++)
    {
      dispChars[i][j] = 0;
    }
  }
  lcdDisplay->init();
  lcdDisplay->backlight();
  lcdDisplay->noAutoscroll();
  lcdDisplay->print("Ok");
}

void DebugDisplay::clear()
{
  lcdDisplay->clear();
}

void DebugDisplay::println(char* message, ...)
{
  char buf[40];
  va_list argList;
  va_start(argList, message);
  vsprintf(buf, message, argList);
  va_end(argList);
  rawPrint(buf);
  scrollUp();  
}

void DebugDisplay::print(char* message, ...)
{
  char buf[40];
  va_list argList;
  va_start(argList, message);
  vsprintf(buf, message, argList);
  va_end(argList);
  rawPrint(buf);
}

void DebugDisplay::rawPrint(char* text)
{
  char len = strlen(text);
  
  if (x == MAXCOLUMNS)
  {
    scrollUp();
  }
 
  if (x + len <= MAXCOLUMNS)
  {
    lcdDisplay->print(text);
    while (len--)
    {
      dispChars[y][x] = text[0];
      x++;
      text++;
    }
  }
  else
  {
    char buf2[40];
    char rl = MAXCOLUMNS - x;
    strncpy(buf2, text, rl);

    buf2[rl] = 0;
    rawPrint(buf2);
    scrollUp();
    strcpy(buf2, text + rl);
    rawPrint(buf2);
  }
}

void DebugDisplay::scrollUp()
{
  if (y < MAXROWS - 1)
  {
    x = 0;
    y++;
    lcdDisplay->setCursor(x, y);
  }
  else
  {
    char buf2[40];
    for (char i = 0; i < MAXCOLUMNS; i++)
    {
      dispChars[0][i] = dispChars[1][i];
    }      
    strncpy(buf2, dispChars[0], MAXCOLUMNS);
    lcdDisplay->setCursor(0, 0);
    lcdDisplay->print(buf2);
    lcdDisplay->setCursor(0, 1);
    lcdDisplay->print("                ");
    lcdDisplay->setCursor(0, 1);
    x = 0;
    y = 1;
  }
}  

void DebugDisplay::showLine(int row, char* message, ...)
{
  char buf[40];
  va_list argList;
  va_start(argList, message);
  vsprintf(buf, message, argList);
  va_end(argList);
  
  char i = strlen(buf);
  char l = lastLen[row];
  while (i < l && i < MAXCOLUMNS)
  {
    buf[i++] = ' ';
  }
  buf[i] = 0;
  lastLen[row] = i;
  lcdDisplay->setCursor(0, row);
  lcdDisplay->print(buf);
}  
    
