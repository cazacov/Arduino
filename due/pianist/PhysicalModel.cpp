#include "PhysicalModel.h"
#include <arduino.h>

void PhysicalModel::InitAcc(int targetPosition, int deccelerationSpeed, Logger* lg)
{
  MaxSpeed = 0;
  for (int i = 0; i < 30; i++)
  {
    DecPath[i] = 0;
  }

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

  // find stopPoint
  int stopPoint;
  for (stopPoint = 100; stopPoint <= lg->logPos; stopPoint++)
  {
    if (lg->lg[stopPoint].Decision <= 0)
    { 
      break;
    }
  }

  int decPos = 0;
  int prevSpeed = lg->lg[stopPoint].Decision;
  
  for (int i = stopPoint; i>0 && lg->lg[i].MotorSpeed <= 0; i--)
  {
    decPos+= lg->lg[i].Decision;
    if (lg->lg[i].Decision > prevSpeed)
    {
      DecPath[prevSpeed] = decPos;
      prevSpeed = lg->lg[i].Decision;
    } 
  }
  
  if (DecPath[prevSpeed] == 0)
  {
    DecPath[prevSpeed] = decPos;
  }
  
  while (prevSpeed < MaxSpeed)
  {
    DecPath[prevSpeed+1] = DecPath[prevSpeed];      
    prevSpeed++;
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
  
  /*
  Serial.println("Dec path");
  for (int i = 0; i <= MaxSpeed; i++)
  {
      sprintf(buf, "%d %d", i, DecPath[i]); 
      Serial.println(buf);
  } 
 */ 
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
