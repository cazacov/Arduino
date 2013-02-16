#ifndef LOGGER_h_
#define LOGGER_h_ 
#define LOGSIZE 500

#include "arduino.h"

class CarriageLogEntry
{
  public:
    int Position;
    int MotorSpeed;
};

class Logger
{
  private:
    CarriageLogEntry lg[LOGSIZE];
    int logPos;
  public:
    Logger();
    void Clear();
    boolean AddToLog(int position, int speed);
    void FlushToSerial();
};

#endif
