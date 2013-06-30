// melody.h
#ifndef _MELODY_h
#define _MELODY_h

#include "arduino.h"

class Melody
{
  private:
    int notePosition(char* note);
    int noteLength(char* note);    
    char buffer[250];
    char* notePos;
  public:
    Melody();
    void init(char* song);
    void start();
    int getHandPosition();
    int getNoteLength();
    int isFinished();
    void nextNote();
    uint8_t getActiveFinger();
};
#endif
