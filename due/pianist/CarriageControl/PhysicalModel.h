#ifndef PHYSICALMODEL_h_
#define PHYSICALMODEL_h_

#include "Logger.h"

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
    int DecPath[30];

    int LastEstimation;
  
//    PhysicalModel();
    int CalculateMotorSpeed(int delta, int currentSpeed, MovingPhase &movingPhase);
    void InitAcc(int targetPosition, int deccelerationSpeed, Logger* lg);
    void ShowEstimations();
};


#endif

