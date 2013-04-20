#ifndef PHYSICALMODEL_h_
#define PHYSICALMODEL_h_

#include "Logger.h"

#define MAXSPEED 30

enum MovingPhase 
{ mpAcceleration,
  mpDeceleration, 
  mpStop
};

class PhysicalModel
{
  private:
    char buf[50];
  public:
    int MaxSpeed;
    int DecPath[MAXSPEED];

    int LastEstimation;
  
//    PhysicalModel();
    int CalculateMotorSpeed(int delta, int currentSpeed, MovingPhase &movingPhase);
    void InitAcc(int targetPosition, int deccelerationSpeed, Logger* lg);
    void ShowEstimations();
};


#endif

