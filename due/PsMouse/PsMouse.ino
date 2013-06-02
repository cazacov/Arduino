#include <ps2.h>

/*
 * an arduino sketch to interface with a ps/2 mouse.
 * Also uses serial protocol to talk back to the host
 * and report what it finds.
 */

/*
 * Pin 2 is the mouse data pin, pin 3 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
 
PS2Mouse mouse(40, 38);

void setup()
{
  Serial.begin(57600);
  Serial.println("Initializing...");  
  mouse.init();
  Serial.println("Initialized");
}

/*
 * get a reading from the mouse and report it back to the
 * host via the serial line.
 */
void loop()
{
  MouseInfo mouseInfo;
  mouse.getData(&mouseInfo);
  
  Serial.print(mouseInfo.status, DEC);
  
  //X change
  Serial.print("\tX=");
  Serial.print(mouseInfo.x, DEC);
  
  //Y change
  Serial.print("\tY=");
  Serial.print(mouseInfo.y, DEC);
  
  //Scroll change
  Serial.print("\tSc=");
  Serial.print(mouseInfo.scroll, DEC);
  
  //Left button down
  Serial.print("\tLB=");
  Serial.print(mouseInfo.leftClick, DEC);
  
  //Middle button down
  Serial.print("\tMB=");
  Serial.print(mouseInfo.middleClick, DEC);
  
  //Right button down
  Serial.print("\tRB=");
  Serial.print(mouseInfo.rightClick, DEC);
  
  //Cumulative X position
  Serial.print("\tCX=");
  Serial.print(mouseInfo.cX, DEC);
  
  //Cumulatie Y position
  Serial.print("\tCY=");
  Serial.print(mouseInfo.cY, DEC);
  
  //Cumulative scroll postion
  Serial.print("\tCS=");
  Serial.print(mouseInfo.cScroll, DEC);
  Serial.println();
}

