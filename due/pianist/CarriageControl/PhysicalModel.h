#ifndef PHYSICALMODEL_h_
#define PHYSICALMODEL_h_

#define LEVELCOUNT 7

class SpeedLevel
{
  public:
    int LowBoundry;
    int HighBoundry;
    int AccDistance;
    int DecDistance;
};    

class PhysicalModel
{
  private:
    SpeedLevel levels[LEVELCOUNT];
  public:
    int LastLevel;
  
    PhysicalModel(int maxSpeed);
    void InitAcceleration(int points, double a, double b, double c, double d);   
    void InitDeceleration(int points, double a, double b, double c, double d);    
    void PrintToSerial();
    
    int MakeDecision(int currentPosition, int targetPosition, int currentSpeed);
};


#endif

