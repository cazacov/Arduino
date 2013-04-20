#include "PhysicalModel.h"
#include <arduino.h>

void PhysicalModel::InitAcc(int targetPosition, int deccelerationSpeed, Logger* lg)
{
  MaxSpeed = 0;
  for (int i = 0; i < MAXSPEED; i++)
  {
    DecPath[i] = 0;
  }

  // ignore first 10 records
  for (int i = 0; i < 10; i++)
  {
    if (lg->lg[i].Position < 0) 
    {
      lg->lg[i].Position = 0;
    }
  }
  
  for (int i = 1; i < lg->logPos; i++)
  {
    lg->lg[i].Decision = lg->lg[i].Position - lg->lg[i-1].Position;  
    if (lg->lg[i].Decision > MaxSpeed)
    {
      MaxSpeed = lg->lg[i].Decision;
    }
  }
  sprintf(buf, "Max speed=%d", MaxSpeed); 
  Serial.println(buf);

  // find stopIndex
  int stopIndex;
  for (stopIndex = 100; stopIndex < lg->logPos; stopIndex++)
  {
    if (lg->lg[stopIndex].Decision <= 0)
    { 
      break;
    }
  }
  sprintf(buf, "Stop index=%d", stopIndex); 
  Serial.println(buf);

  
  // find breakPoint
  int breakIndex;
  for (breakIndex = 10; breakIndex < lg->logPos; breakIndex++)
  {
    if (lg->lg[breakIndex].MotorSpeed <= 0)
    { 
      break;
    }
  }
  sprintf(buf, "Break index=%d", breakIndex); 
  Serial.println(buf);
  
  for (int i = breakIndex; i <= stopIndex; i++)
  {
    int mySpeed = lg->lg[i].Decision;
    int distanceToStop = lg->lg[stopIndex].Position - lg->lg[i].Position;
    
    if (DecPath[mySpeed] == 0)
    {
      DecPath[mySpeed] = distanceToStop;
    }
  }

  // speeds greater then max are set to maximal distance
  int i = MAXSPEED - 1;
  int maxBreakDistance = lg->lg[stopIndex].Position - lg->lg[breakIndex].Position;
  
  while (DecPath[i] == 0 && i > 0)
   {
    DecPath[i--] = maxBreakDistance;
  }
  
  // close gaps
  for (int p1 = 1; p1 < MaxSpeed; p1++)
  {
     if (DecPath[p1] == 0)
     {   
       int p2 = p1+1;
       while(p2 < MaxSpeed && DecPath[p2] == 0)
       {
         p2++;
       }
       int x1 = DecPath[p1-1];
       int x2 = DecPath[p2];
       
       for (int p = 0; p < p2-p1; p++)
       {
         DecPath[p1 + p] = x1 + (x2-x1) * (p+1) / (p2-p1+1);
       }
       p1 = p2;
     }
  }
  
  ShowEstimations();
}

int PhysicalModel::CalculateMotorSpeed(int delta, int currentSpeed, MovingPhase &movingPhase)
{
  if (movingPhase == mpStop || 
    (movingPhase == mpDeceleration && currentSpeed < 0))
  {
      // target reached
      movingPhase = mpStop;
      return 0;
  }    
  
  if (currentSpeed > MaxSpeed)
  {
    currentSpeed = MaxSpeed;
  }
  int estimatedBreakDistance = DecPath[currentSpeed];
  LastEstimation = estimatedBreakDistance;
  int diff = delta - estimatedBreakDistance;
  
  if (movingPhase == mpAcceleration && (diff > currentSpeed/2))
  {
    return 255;
  }
  else
  {
    movingPhase = mpDeceleration;
  }
  
  if (fabs(diff) < currentSpeed / 2)
  {
    return -220;
  }
  
  if (diff > 0)
  {
    return -220.0 * (double)delta / estimatedBreakDistance;
  }
  else
  {
    return -220.0  + diff;
  }
}

void PhysicalModel::ShowEstimations()
{
  Serial.print("Max speed: ");
  Serial.println(MaxSpeed);
  
  for (int i = 0; i <= MaxSpeed; i++)
  {
      sprintf(buf, "%d %d", i, DecPath[i]); 
      Serial.println(buf);
  }  
}
