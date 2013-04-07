#ifndef LOGGER_h_
#define LOGGER_h_ 
#define LOGSIZE 500

#include "arduino.h"

class CarriageLogEntry
{
  public:
    int Position;
    int MotorSpeed;
    int Decision;
};

class Logger
{
  public:
    CarriageLogEntry lg[LOGSIZE];
    int logPos;
    Logger();
    void Clear();
    boolean AddToLog(int position, int speed, int decision = 0);
    void FlushToSerial();
};

#endif
