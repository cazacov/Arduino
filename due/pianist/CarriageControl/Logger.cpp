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
    lg[i].Position = lg[i].MotorSpeed = 0;
  }
}

boolean Logger::AddToLog(int position, int speed)
{
  if (logPos >= LOGSIZE)
  {
    return false;
  }
  
  lg[logPos].Position = position;
  lg[logPos].MotorSpeed = speed;
  
  logPos++;
}

void Logger::FlushToSerial()
{
  char buf[30];
  
  sprintf(buf, "Log size: %d", logPos);
  Serial.println(buf);
  
  for (int i = 0; i < logPos; i++)
  {
      sprintf(buf, "%d\t%d\t%d", i, lg[i].MotorSpeed, lg[i].Position);
      Serial.println(buf);
  }      
}

