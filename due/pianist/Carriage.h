#ifndef CARRIAGE_h_
#define CARRIAGE_h_ 

#include "arduino.h"
#include "pins_arduino.h"
#include "PhysicalModel.h"

class CarriageDriver
{
  private:
    void ResetPosition();
    boolean IsAtTheEnd();
    void SetMotorSpeed(int newSpeed);
    //
    unsigned char endSensorPin;
    unsigned char quad_A;
    unsigned char quad_B;
    unsigned char motorDirectionPin;
    unsigned char motorSpeedPin;    
    unsigned int mask_quad_A;
    unsigned int mask_quad_B;  
    char buf[40];
  public:
    CarriageDriver(unsigned char endSesnorPinNr);
    long GetPosition();
    void Calibrate();
    void SpeedCheck2(PhysicalModel* pm);    
    void MoveABit();
    void GoRaw(int newPosition);
    void GoExact(int newPosition, PhysicalModel* pm);    
};


#endif
