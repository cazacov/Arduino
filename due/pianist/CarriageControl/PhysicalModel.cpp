#include "PhysicalModel.h"
#include <arduino.h>

PhysicalModel::PhysicalModel(int maxSpeed)
{
  levels[0].LowBoundry = 0;  
  levels[0].HighBoundry = 1;

  int nxtBound = levels[0].HighBoundry + 1;
  for (int i = 1; i < LEVELCOUNT; i++)
  {
    levels[i].LowBoundry = nxtBound;
    levels[i].HighBoundry = (maxSpeed - 2)*(i)/(LEVELCOUNT-1) + 2;
    nxtBound = levels[i].HighBoundry + 1;
  }      
  for (int i = 0; i < LEVELCOUNT; i++)
  {
    levels[i].AccDistance = levels[i].DecDistance = 0;
  }
}  

void PhysicalModel::InitAcceleration(int points, double a, double b, double c, double d)
{
  int currentLevel = 0;
  double levelDistance = 0;
  
  for (int x = 0; x < points; x++)
  {
    double y = x*x*x*a + x*x*b + x*c + d;
    if (y > levels[currentLevel].HighBoundry)
    {
      levels[currentLevel].AccDistance = levelDistance;
      levelDistance = y;
      currentLevel++;
    }
    else
    {
      levelDistance += y;
    }    
  } 
  if (currentLevel <= LEVELCOUNT && levels[LEVELCOUNT - 1].AccDistance == 0)
  {
    levels[LEVELCOUNT - 1].AccDistance = levelDistance;
  }  
}

void PhysicalModel::InitDeceleration(int points, double a, double b, double c, double d)
{
  int currentLevel = LEVELCOUNT-1;
  double levelDistance = 0;
  
  char buf[40];
  
  for (int x = 1; x < points; x++)
  {
    double y = x*x*x*a + x*x*b + x*c + d;
    sprintf(buf, "%d %d %lf %lf", x, currentLevel, y, levelDistance);
    Serial.println(buf);

    
    if (y < 0)
    {
      y = 0;
    }      
    if (y < levels[currentLevel].LowBoundry)
    {
      if (levelDistance < 1)
      {
        levelDistance = 1;
      }
      levels[currentLevel].DecDistance = levelDistance;
      levelDistance = y;
      currentLevel--;
    }
    else
    {
      levelDistance += y;
    }    
  } 
  if (levelDistance < 1)
  {
    levelDistance = 1;
  }
  if (levels[0].DecDistance == 0)
  {
    levels[0].DecDistance = levelDistance;
  }  
}

void PhysicalModel::PrintToSerial()
{
  char buf[40];
  int sumAcc = 0; 
  int sumDec = 0;  
  
  for (int i = 0; i < LEVELCOUNT; i++)
  {
    sumAcc += levels[i].AccDistance;
    sumDec += levels[i].DecDistance;    
    sprintf(buf, "%d %d-%d\t%d\t%d", i, levels[i].LowBoundry, levels[i].HighBoundry, levels[i].AccDistance, levels[i].DecDistance);
    Serial.println(buf);
  }
  
  sprintf(buf, "Sum acc: %d  dec: %d", sumAcc, sumDec);
  Serial.println(buf);  
}

int PhysicalModel::MakeDecision(int currentPosition, int targetPosition, int currentSpeed)
{
  int xTolerance = 10;
  int sTolerance = 3;  

  if (abs(currentPosition - targetPosition) < xTolerance)
  {
    if (abs(currentSpeed) <= levels[0].HighBoundry)
    {
      // target reached
      Serial.println("T");
      return 0;
    }
  }    
  
  if (currentPosition > targetPosition)
  {
    // inverse x
    return -MakeDecision(targetPosition*2-currentPosition, targetPosition, -currentSpeed);
  }
  
  /* Assumptions:
  currentPos < targetPos;
  */
  
  // find current speed level
  int currentLevel;
  for (currentLevel = 0; currentLevel < LEVELCOUNT; currentLevel++)
  { 
    if (levels[currentLevel].HighBoundry > currentSpeed)
    {
      break;
    }
  }
  if (currentLevel >= LEVELCOUNT)
  {
    currentLevel = LEVELCOUNT - 1;
  }
  LastLevel = currentLevel;
  
  // check full brake scenario
  int decDistance = 0;
  for (int i = 0; i <= currentLevel; i++)
  {
    decDistance += levels[i].DecDistance;
  }
  
  int delta = targetPosition - currentPosition - decDistance;
  
  if (delta < 0)
  {
    // FULL BRAKE!
    return -1;
  }
  else
  {
    if (currentLevel > 0)
    {
      if (delta < currentSpeed)
      {
        // SHORT BREAK
        return -1;
      }
      else
      {
        // ACCELERATE
        return 1;
      }
    }
    else
    {
      // 0-level, we are far enough from the target
      return 1;
    }  
  }
  Serial.println("F");
  return 0;
}  

