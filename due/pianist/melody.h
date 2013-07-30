// melody.h
#ifndef _MELODY_h
#define _MELODY_h

#include "arduino.h"

class Melody
{
  private:
    char songBuffer[250];
    char* notePos;
    int handPosition;
    int noteLength;
    int activeFinger;
    int parseNote(char* note, int& noteKey, int& noteLength, int& byteLength, int& isSharp);
    int noteOffset[12];
    char txtBuffer[30];
    int debugFlag;  
public:
    Melody();
    void init(char* song, int debugFlag);

    // hand position in mm
    int nextNote(int carretPosition);

    // returns next hand position in mm
    int getHandPosition();
    
    // returns next note length in ms
    int getNoteLength();
    
    // returns next active finger 0..4
    int getActiveFinger();
    
    // delay before playing next note in milliseconds
    int delayAfterNote();
};
#endif
