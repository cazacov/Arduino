#include "melody.h"

/* Links
http://www.youtube.com/watch?v=smZr_FHLHwA
http://www.dolmetsch.com/musictheory1.htm
*/

int NORMAL_NOTE_LENGTH = 250;
int LONG_NOTE_LENGTH = 500;

// left side of C4 key is located 81 mm from the hand's zero position
int C4_LEFT_SIDE = 93;
int C4_KEY = 60;  // noteKey as defined in MIDI standart
int OCTAVE_SIZE = 164;
const char *NOTE_NAMES[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

Melody::Melody()
{
  // offset in milimeters from left side of C to the middle of key
    noteOffset = {
    11,  //  C
    22,  //  C#
    35,  //  D 
    49,  //  D#
    59,  //  E
    83,  //  F
    91,  //  F#
    106, //  G
    117, //  G#
    129, //  A   
    144, //  A#
    152  //  B
  };
}

void Melody::init(char* song, int newDebugFlag)
{
  strcpy(songBuffer, song);
  notePos = songBuffer;
  debugFlag = newDebugFlag;
}

int Melody::getHandPosition()
{
  return handPosition;
}

int Melody::getNoteLength()
{
  return noteLength;
}

int Melody::getActiveFinger()
{
  return activeFinger;
}

int Melody::delayAfterNote()
{
  return 200;
}  

int Melody::nextNote(int carretPosition)
{
  if (strlen(notePos) <2)
  {
    // nothing to play
    return 0;
  }
  
  int noteKey;
  int noteDuration;
  int byteLength;
  
  if (!parseNote(notePos, noteKey, noteLength, byteLength))
  {
    return 0;    
  }

  int octavePosition = (noteKey - C4_KEY) % 12; 
  if (octavePosition < 0)
  {
    octavePosition += 12;
  }
    
  int octave = floor((noteKey - C4_KEY) / 12.0);
  
    if (debugFlag)
  {
    sprintf(txtBuffer, "parse %d %d %d", noteKey, noteLength, byteLength);
    Serial.println(txtBuffer);    
  }
  
  int notePosition = C4_LEFT_SIDE + octave * OCTAVE_SIZE + noteOffset[octavePosition];
  
  activeFinger = 4;
  handPosition = notePosition;
  
  notePos+= byteLength;
  return 1;
}

/* 
  Returns MIDI key for the specified note.
  Uses C4-convention 
  C4 = 60,
  E5 = 76,
  etc
*/    
int Melody::parseNote(char* note, int& noteKey, int& noteLength, int& byteLength)
{
  if (strlen(note) < 2)
  {
    return 0;
  } 
 
  int noteNumber;
  int octave;

  int i;
  for (i = 0; i < 12; i++)
  {
    int testStrLen = strlen(NOTE_NAMES[i]);
    if (strncmp(note, NOTE_NAMES[i], testStrLen) == 0)
    {
      if (testStrLen == 1 && note[1] == '#')
      {
        continue;
      }
      
      noteNumber = i;
      byteLength = testStrLen;
      
      if (strlen(note) > byteLength)
      {
        octave = note[byteLength] - '0';
        byteLength++;
      }        
      noteKey = noteNumber + octave * 12 + 12;
      
      if (strlen(note) > byteLength && note[byteLength] == '+')
      {
        noteLength = LONG_NOTE_LENGTH;
        byteLength++;
      }
      else
      {
        noteLength = NORMAL_NOTE_LENGTH;
      }    
      
      // skip spaces after note
      while(note[byteLength] == ' ')
      {
        byteLength++;
      }
      return 1;
    }
  }
  if (i == 12)
  {
    return 0;
  }
}
  

  
