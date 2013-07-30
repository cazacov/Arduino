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
const int FINGER_POSITIONS[5] = { 96, 72, 48, 24, 0 };

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
  int isSharp;
  
  if (!parseNote(notePos, noteKey, noteLength, byteLength, isSharp))
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
    sprintf(txtBuffer, "parse %d %d %d %d", noteKey, noteLength, byteLength, isSharp);
    Serial.println(txtBuffer);    
  }
  
  int positionsForFingers[5];
  for (int i = 0; i < 5; i++)
  {
    positionsForFingers[i] = C4_LEFT_SIDE + octave * OCTAVE_SIZE + noteOffset[octavePosition] - FINGER_POSITIONS[i];
  }
  
  if (isSharp)
  {
    positionsForFingers[0] = positionsForFingers[4] = -1000; // sharp notes cannot be played with these fingers
    activeFinger = 3; // start value
  }
  else
  {
    positionsForFingers[1] = positionsForFingers[2] = positionsForFingers[3] = - 1000; // non-sharp notes cannot be played with these fingers
    activeFinger = 4; // start value    
  }
  
  int distance = 500;
  
  for (int i = 0; i < 5; i++)
  {
    // ignore negative and very small positions
    if (positionsForFingers[i] < 5)
    {
      continue;
    }
    
    int curDistance = abs(carretPosition - positionsForFingers[i]);
    if ((isSharp && curDistance < 3) || (!isSharp && curDistance < 5))
    {
      // finger is already in tolerance interval above the desired note
      activeFinger = i;
      distance = curDistance;
    }
    if (curDistance < 35)
    {
      // hand cannot be moved precisely on short distances
      continue;
    }
    else if (curDistance < distance)
    {
      distance = curDistance;
      activeFinger = i;
    }
  }
  handPosition = positionsForFingers[activeFinger];
  
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
int Melody::parseNote(char* note, int& noteKey, int& noteLength, int& byteLength, int &isSharp)
{
  if (strlen(note) < 2)
  {
    return 0;
  } 
 
  int noteNumber;
  int octave;

  int i;
  isSharp = 0;
  for (i = 0; i < 12; i++)
  {
    int testStrLen = strlen(NOTE_NAMES[i]);
    if (strncmp(note, NOTE_NAMES[i], testStrLen) == 0)
    {
      if (testStrLen == 1 && note[1] == '#')
      {
        continue;
      }
      
      isSharp = (note[1] == '#');
      
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
  

  
