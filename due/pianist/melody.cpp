#include "melody.h"

/* Links
http://www.youtube.com/watch?v=smZr_FHLHwA
http://www.dolmetsch.com/musictheory1.htm
*/

Melody::Melody()
{
  ;
}

void Melody::init(char* song)
{
  strcpy(buffer, song);
  notePos = buffer;
}

void Melody::start()
{
  notePos = buffer;  
}

int Melody::getHandPosition()
{
  return notePosition(notePos);
}

int Melody::getNoteLength()
{
  return noteLength(notePos);
}

int Melody::isFinished()
{
  return strlen(notePos) < 3;
}

void Melody::nextNote()
{
  if (strlen(notePos) >=3)
  {
    notePos += 4;
  }
  else
  {
    notePos += strlen(notePos);
  }
}

uint8_t Melody::getActiveFinger()
{
  return 4;
}

int Melody::notePosition(char* note)
{
  int step = 550;
  int posC4 = 2300;
  
  if (strlen(note) < 3)
  {
    return posC4;
  }
  
  return (note[1] - '4') * step * 7 + ((note[0] - 'A' + 5) % 7) * step + posC4;  
}

int Melody::noteLength(char* note)
{
  int lengthIndex = 3;
  int defaultLength = 250;
  
  if (strlen(note) < 3)
  {
    return defaultLength;
  }
  if (note[lengthIndex] == ' ')
  {
    return defaultLength;  
  }
    if (note[lengthIndex] == '+')
  {
    return defaultLength*2;  
  }
  else
  {
    return defaultLength;
  }
}
    
  
