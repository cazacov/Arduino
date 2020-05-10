#include <AFMotor.h>
#include <Servo.h> 
 
#define START_X  10
#define START_Y  9
#define SERVO_PIN 2
 
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
  motorX.step(5, FORWARD, INTERLEAVE);
  motorY.step(5, FORWARD, INTERLEAVE);     
  posX = 0;
  posY = 0;
}
 
void loop() 
{
  for (int i = 0; i <75; i+=5)
  {
    goTo(i, i);
    penDown();
    goTo(150 - i, i);    
    goTo(150 - i, 150 - i);        
    goTo(i, 150 - i);            
    goTo(i, i);            
    penUp();
  }
  
  penUp();
  while(1);
  
  return;
  
  int r = 70;
  goTo(75 + r, 75);
  delay(200);
  

  

  
  char buf[20];
  
  float phi = 0;
  for (float phi = 0; phi < 3.1415926 * 2; phi+= 3.1415 / 10.01)
  {
    int x = 75.0 + cos(phi) * r;
    int y = 75.0 + sin(phi) * r;   
 
    sprintf(buf, "%d\t%d", x, y);
    Serial.println(buf);
    goTo(x, y);
  }
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

void penUp()
{
  penServo.write(100);
  delay(600);
}

void penDown()
{
  penServo.write(60);
  delay(600);  
}


