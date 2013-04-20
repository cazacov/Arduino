#ifndef PHYSICALMODEL_h_
#define PHYSICALMODEL_h_

#include "Logger.h"

#define MAXSPEED 30

#define FULL_MOTOR_POWER  250
#define MEDIUM_MOTOR_POWER  200

enum MovingPhase 
{ mpAcceleration,
  mpDeceleration, 
  mpStop
};

class PhysicalModel
{
  private:
    char buf[50];
    int maxSpeed;
    int brakingDistance[2][MAXSPEED];
  void showEstimations(int8_t moveDirection);
  public:
    PhysicalModel();
    int lastEstimation;
  
//    PhysicalModel();
    int calculateMotorSpeed(int delta, int currentSpeed, MovingPhase &movingPhase, int8_t moveDirection);
    void calculateBrakingDistance(Logger* lg, int8_t moveDirection);
};
#endif

