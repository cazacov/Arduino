#include "PhysicalModel.h"
#include <arduino.h>

PhysicalModel::PhysicalModel()
{
  maxSpeed = 0;
}

void PhysicalModel::calculateBrakingDistance(Logger* lg, int8_t moveDirection)
{
  uint8_t arrayIndex = moveDirection > 0 ? 0 : 1;
  
  for (int i = 0; i < MAXSPEED; i++)
  {
    brakingDistance[arrayIndex][i] = 0;
  }

  // ignore first 10 records
  for (int i = 0; i < 10; i++)
  {
    if (lg->lg[i].position < 0) 
    {
      lg->lg[i].position = 0;
    }
  }
  
  for (int i = 1; i < lg->logPos; i++)
  {
    lg->lg[i].parameter = (lg->lg[i].position - lg->lg[i-1].position) * moveDirection;  
    if (lg->lg[i].parameter > maxSpeed)
    {
      maxSpeed = lg->lg[i].parameter;
    }
  }
  sprintf(buf, "Max speed=%d", maxSpeed); 
  Serial.println(buf);

  // find stopIndex
  int stopIndex;
  for (stopIndex = 100; stopIndex < lg->logPos; stopIndex++)
  {
    if (lg->lg[stopIndex].parameter <= 0)
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
    if (lg->lg[breakIndex].motorSpeed * moveDirection <= 0)
    { 
      break;
    }
  }
  sprintf(buf, "Break index=%d", breakIndex); 
  Serial.println(buf);
  
  for (int i = breakIndex; i <= stopIndex; i++)
  {
    int mySpeed = lg->lg[i].parameter;
    int distanceToStop = (lg->lg[stopIndex].position - lg->lg[i].position) * moveDirection;
    
    if (brakingDistance[arrayIndex][mySpeed] == 0)
    {
      brakingDistance[arrayIndex][mySpeed] = distanceToStop;
    }
  }

  // speeds greater then max are set to maximal distance
  int i = MAXSPEED - 1;
  int maxBreakDistance = (lg->lg[stopIndex].position - lg->lg[breakIndex].position) * moveDirection;
  
  while (brakingDistance[arrayIndex][i] == 0 && i > 0)
   {
    brakingDistance[arrayIndex][i--] = maxBreakDistance;
  }
  
  // close gaps
  for (int p1 = 1; p1 < maxSpeed; p1++)
  {
     if (brakingDistance[arrayIndex][p1] == 0)
     {   
       int p2 = p1+1;
       while(p2 < maxSpeed && brakingDistance[arrayIndex][p2] == 0)
       {
         p2++;
       }
       int x1 = brakingDistance[arrayIndex][p1-1];
       int x2 = brakingDistance[arrayIndex][p2];
       
       for (int p = 0; p < p2-p1; p++)
       {
         brakingDistance[arrayIndex][p1 + p] = x1 + (x2-x1) * (p+1) / (p2-p1+1);
       }
       p1 = p2;
     }
  }
  showEstimations(moveDirection);
}

int PhysicalModel::calculateMotorSpeed(const int delta, int currentSpeed, MovingPhase &movingPhase, const int8_t moveDirection)
{
  if (movingPhase == mpStop || 
    (movingPhase == mpDeceleration && currentSpeed < 0))
  {
      // target reached
      movingPhase = mpStop;
      return 0;
  }    
  
  if (currentSpeed > maxSpeed)
  {
    currentSpeed = maxSpeed;
  }
  
  lastEstimation = brakingDistance[moveDirection > 0 ? 0 : 1][currentSpeed];
  int diff = delta - lastEstimation;
  
  if (movingPhase == mpAcceleration && diff > (currentSpeed >> 2))
  {
    return FULL_MOTOR_POWER;
  }
  else
  {
    movingPhase = mpDeceleration;
  }
  
  if (abs(diff) < (currentSpeed >> 1))
  {
    return -MEDIUM_MOTOR_POWER;
  }
  
  if (diff > 0)
  {
    return long(-MEDIUM_MOTOR_POWER) * lastEstimation / delta;
  }
  else
  {
    return -FULL_MOTOR_POWER  + diff;
  }
}

void PhysicalModel::showEstimations(int8_t moveDirection)
{
  sprintf(buf, "Direction: %d, Max speed: %d", (int)moveDirection, maxSpeed);
  Serial.println(buf);
  
  for (int i = 0; i <= maxSpeed; i++)
  {
      sprintf(buf, "%d %d", i, brakingDistance[moveDirection > 0 ? 0 : 1][i]); 
      Serial.println(buf);
  }  
}
