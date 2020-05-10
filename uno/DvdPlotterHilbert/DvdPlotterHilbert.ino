#include <AFMotor.h>
#include <Servo.h> 
 
#define START_X  10
#define START_Y  9
#define SERVO_PIN 2
#define CURVE_ORDER 6
#define LINE_LENGTH 5
 
AF_Stepper motorX(48, 1);
AF_Stepper motorY(48, 2);
Servo penServo;  

void goTo(int newX, int newY); 
void penUp(); 
void penDown(); 

int posX, posY;
 
void setup() {
  penServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
  penUp();
  
  Serial.begin(115200);
  pinMode(START_X, INPUT); 
  pinMode(START_Y, INPUT);   
  motorX.setSpeed(160);  // 10 rpm   
  motorY.setSpeed(100);  // 10 rpm     
  
  // Move to the start position
  while(digitalRead(START_X))
  {
    motorX.step(1, BACKWARD, INTERLEAVE);
    delay(5);
  }
  while(digitalRead(START_Y))
  {
    motorY.step(1, BACKWARD, INTERLEAVE);
    delay(5);
  }
  motorX.step(2, FORWARD, INTERLEAVE);
  motorY.step(2, FORWARD, INTERLEAVE);     
  posX = 0;
  posY = 0;
  penUp();
  goTo(0,0);
}

void HU(int n);
void HD(int n);
void HL(int n);
void HR(int n);
 
void loop() 
{
  delay(1000);
  penDown();
  HU(CURVE_ORDER);
  penUp();
  
  while(1);
}

void goTo(int newX, int newY)
{
  newX <<= 1;
  newY <<= 1;  
  if (newX > posX)
  {
    motorX.step(newX - posX, FORWARD, INTERLEAVE);
  }
  else if (newX < posX)
  {
    motorX.step(posX - newX, BACKWARD, INTERLEAVE);
  }
  posX = newX;

  if (newY > posY)
  {
    motorY.step(newY - posY, FORWARD, INTERLEAVE);
  }
  else if (newY < posY)
  {
    motorY.step(posY - newY, BACKWARD, INTERLEAVE);
  }
  posY = newY;
//  motorX.release();
//  motorY.release();  
}

void lineRel(int relX, int relY)
{

  if (relX > 0)
  {
    motorX.step(relX, FORWARD, INTERLEAVE);
  }
  else if (relX < 0)
  {
    motorX.step(-relX, BACKWARD, INTERLEAVE);
  }

  if (relY > 0)
  {
    motorY.step(relY, FORWARD, INTERLEAVE);
  }
  else if (relY < 0)
  {
    motorY.step(-relY, BACKWARD, INTERLEAVE);
  }
}

void penUp()
{
  penServo.write(100);
  delay(600);
}

void penDown()
{
  penServo.write(47);
  delay(600);  
}

void HU(int n)
{
  if (n == 0)
    return;
  HR(n-1);
  lineRel(0, LINE_LENGTH);
  HU(n - 1);
  lineRel(LINE_LENGTH, 0);
  HU(n-1);
  lineRel(0, -LINE_LENGTH);  
  HL(n-1);
}

void HD(int n)
{
  if (n == 0)
    return;
  HL(n-1);
  lineRel(0, -LINE_LENGTH);
  HD(n - 1);
  lineRel(-LINE_LENGTH, 0);
  HD(n-1);
  lineRel(0, LINE_LENGTH);  
  HR(n-1);
}

void HL(int n)
{
  if (n == 0)
    return;
  HD(n-1);
  lineRel(-LINE_LENGTH, 0);
  HL(n - 1);
  lineRel(0, -LINE_LENGTH);
  HL(n-1);
  lineRel(LINE_LENGTH, 0);  
  HU(n-1);
}

void HR(int n)
{
  if (n == 0)
    return;
  HU(n-1);
  lineRel(LINE_LENGTH, 0);
  HR(n - 1);
  lineRel(0, LINE_LENGTH);
  HR(n-1);
  lineRel(-LINE_LENGTH, 0);  
  HD(n-1);
}
