#include "wwFlipdotPar.h"

// ===========================================================================================
void setup() {
  dotSetup( 8, 21, 1, 19, 0);  //19x21
  dotPowerOn();    //schaltet den DC/DC Wandler für die Flipspannung ein
  delay(50);       //kurze Wartezeit, um den Spannungswandler auf Touren kommen zu lassen
  resetAll(5);     //lösche alle Dots mit 5 ms Verzögerung
}
// ===========================================================================================
void loop() {
  drawSmile(4, 3);

  while(true);
}
// ===========================================================================================

void drawSmile(uint8_t x0, uint8_t y0)
{
  for (uint8_t x = 1; x <= 21; x++)
    for (uint8_t y = 1; y <= 19; y++)
    {
      setDot(x, y);
      delay(20);
    }

  resetDot(x0, y0+5);  
  resetDot(x0, y0+6);
  resetDot(x0, y0+7);
  resetDot(x0, y0+8);  
  resetDot(x0, y0+9);  

  resetDot(x0+1, y0+3);  
  resetDot(x0+1, y0+4);
  resetDot(x0+1, y0+5);
  resetDot(x0+1, y0+10);  
  resetDot(x0+1, y0+11);  

  resetDot(x0+2, y0+2);  
  resetDot(x0+2, y0+5);
  resetDot(x0+2, y0+6);
  resetDot(x0+2, y0+7);  
  resetDot(x0+2, y0+12);  

  resetDot(x0+3, y0+1);  
  resetDot(x0+3, y0+5);
  resetDot(x0+3, y0+8);
  resetDot(x0+3, y0+13);  

  resetDot(x0+4, y0+1);  
  resetDot(x0+4, y0+5);
  resetDot(x0+4, y0+7);
  resetDot(x0+4, y0+8);  
  resetDot(x0+4, y0+13);  

  resetDot(x0+5, y0);  
  resetDot(x0+5, y0+5);
  resetDot(x0+5, y0+6);
  resetDot(x0+5, y0+7);  
  resetDot(x0+5, y0+8);    
  resetDot(x0+5, y0+14);  

  resetDot(x0+6, y0);  
  resetDot(x0+6, y0+5);
  resetDot(x0+6, y0+6);
  resetDot(x0+6, y0+7);  
  resetDot(x0+6, y0+11);    
  resetDot(x0+6, y0+14);    

  resetDot(x0+7, y0);  
  resetDot(x0+7, y0+5);
  resetDot(x0+7, y0+6);
  resetDot(x0+7, y0+11);    
  resetDot(x0+7, y0+14);    

  resetDot(x0+8, y0);  
  resetDot(x0+8, y0+5);
  resetDot(x0+8, y0+6);
  resetDot(x0+8, y0+7);  
  resetDot(x0+8, y0+11);    
  resetDot(x0+8, y0+14);    

  resetDot(x0+9, y0);  
  resetDot(x0+9, y0+5);
  resetDot(x0+9, y0+8);
  resetDot(x0+9, y0+11);    
  resetDot(x0+9, y0+14);    

  resetDot(x0+10, y0+1);  
  resetDot(x0+10, y0+5);
  resetDot(x0+10, y0+7);  
  resetDot(x0+10, y0+8);
  resetDot(x0+10, y0+10);    
  resetDot(x0+10, y0+13);    

  resetDot(x0+11, y0+1);  
  resetDot(x0+11, y0+5);
  resetDot(x0+11, y0+6);  
  resetDot(x0+11, y0+7);  
  resetDot(x0+11, y0+8);
  resetDot(x0+11, y0+13);    

  resetDot(x0+12, y0+2);  
  resetDot(x0+12, y0+5);
  resetDot(x0+12, y0+6);  
  resetDot(x0+12, y0+7);  
  resetDot(x0+12, y0+12);    

  resetDot(x0+13, y0+3);  
  resetDot(x0+13, y0+4);
  resetDot(x0+13, y0+5);  
  resetDot(x0+13, y0+10);  
  resetDot(x0+13, y0+11);    

  resetDot(x0+14, y0+5);  
  resetDot(x0+14, y0+6);
  resetDot(x0+14, y0+7);  
  resetDot(x0+14, y0+8);  
  resetDot(x0+14, y0+9);    
}


