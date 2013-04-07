#include "Logger.h"

Logger::Logger()
{
  Clear();
}

void Logger::Clear()
{
  logPos = 0;
  for (int i = 0; i < LOGSIZE; i++)
  {
    lg[i].Position = lg[i].MotorSpeed = lg[i].Decision=0;
  }
}

boolean Logger::AddToLog(int position, int speed, int decision)
{
  if (logPos >= LOGSIZE)
  {
    return false;
  }
  
  lg[logPos].Position = position;
  lg[logPos].MotorSpeed = speed;
  lg[logPos].Decision = decision;  
  
  logPos++;
}

void Logger::FlushToSerial()
{
  char buf[40];
  
  sprintf(buf, "Log size: %d", logPos);
  Serial.println(buf);
  
  for (int i = 0; i < logPos; i++)
  {
      sprintf(buf, "%d\t%d\t%d\t%d", i, lg[i].MotorSpeed / 10, lg[i].Position, lg[i].Decision);
      Serial.println(buf);
  }      
}

