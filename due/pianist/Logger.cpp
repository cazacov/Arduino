#include "Logger.h"

Logger::Logger()
{
  clear();
}

void Logger::clear()
{
  logPos = 0;
  for (int i = 0; i < LOGSIZE; i++)
  {
    lg[i].position = lg[i].motorSpeed = lg[i].parameter=0;
  }
}

boolean Logger::addToLog(int position, int speed, int parameter)
{
  if (logPos >= LOGSIZE)
  {
    return false;
  }
  
  lg[logPos].position = position;
  lg[logPos].motorSpeed = speed;
  lg[logPos].parameter = parameter;  
  
  logPos++;
}

void Logger::flushToSerial()
{
  char buf[40];
  
  sprintf(buf, "Log size: %d", logPos);
  Serial.println(buf);
  
  for (int i = 0; i < logPos; i++)
  {
      sprintf(buf, "%d\t%d\t%d\t%d", i, lg[i].position, lg[i].motorSpeed, lg[i].parameter);
      Serial.println(buf);
  }      
}

