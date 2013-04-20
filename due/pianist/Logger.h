#ifndef LOGGER_h_
#define LOGGER_h_ 
#define LOGSIZE 500

#include "arduino.h"

class CarriageLogEntry
{
  public:
    int position;
    int motorSpeed;
    int parameter;
};

class Logger
{
  public:
    Logger();
    
    CarriageLogEntry lg[LOGSIZE];
    int logPos;
    
    void clear();
    boolean addToLog(int position, int speed, int parameter = 0);
    void flushToSerial();
};

#endif
