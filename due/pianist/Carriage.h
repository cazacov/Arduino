#ifndef CARRIAGE_h_
#define CARRIAGE_h_ 

#include "arduino.h"
#include "pins_arduino.h"
#include "PhysicalModel.h"

#define DIR_FORWARD 1
#define DIR_BACK -1
#define TICKS_PER_METER 23467
#
#define LIMIT_LEFT 4
#define LIMIT_RIGHT 328

// Processing cycle in microseconds
#define PROCESSING_CYCLE 1000

class CarriageDriver
{
  private:
    unsigned char endSensorPin;
    unsigned char quad_A;
    unsigned char quad_B;
    unsigned char motorDirectionPin;
    unsigned char motorSpeedPin;    
    unsigned int mask_quad_A;
    unsigned int mask_quad_B;  
    char buf[40];
    PhysicalModel pm;        

    void resetPosition();
    boolean isAtTheEnd();
    void setMotorSpeed(int newSpeed);
    void speedCheck(int8_t direction);    
    void moveABit();
    int targetPosition;
    int8_t moveDirection;
    long nxtTime;
    MovingPhase movingPhase;
    int prevPos;
  public:
    CarriageDriver(unsigned char endSesnorPinNr);
    long getPosition();
    void calibrate();
    void goToPosition(int newPosition);    
    int getPosMm();
    void goToPosMm(int newPositionMm);
    volatile uint8_t is_moving;
    void processEvents();
};


#endif
