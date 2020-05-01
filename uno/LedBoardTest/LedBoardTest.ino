// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      240

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
  Serial.begin(9600);
}

#define TURTLES 3

int cor[TURTLES][2] = {{2,3}, {10,5}, {16,7}};
int spd[TURTLES][2] = {{1,1}, {1,2}, {-2,1}};

void setPixel(int x, int y, uint32_t color)
{
  int c = y * 24;
  if (y % 2)
  {
    c+=x;
  }
  else
  {
    c+=23-x;
  }
  pixels.setPixelColor(c, color);  
}

void loop() {
  
  setPixel(5,0,0xCC0000L);
  setPixel(5,1,0x00CC00L);
  setPixel(5,2,0x0000CCL);
  setPixel(6,0,0xCCCC00L);
  setPixel(6,1,0x00CCCCL);
  setPixel(6,2,0xCC00CCL);
  setPixel(7,1,0xCCCCCCL);
  pixels.show(); 
//  return;

  for(int i=0; i<TURTLES; i++) {
    {
      setPixel(cor[i][0], cor[i][1], 0);
      
      cor[i][0] += spd[i][0];
      if (cor[i][0] < 0)
      {
        cor[i][0] = -cor[i][0];
        spd[i][0] = -spd[i][0];
      }
      if (cor[i][0] > 23)
      {
        cor[i][0] = 46 - cor[i][0];
        spd[i][0] = -spd[i][0];
      }

      cor[i][1] += spd[i][1];
      if (cor[i][1] < 0)
      {
        cor[i][1] = -cor[i][1];
        spd[i][1] = -spd[i][1];
      }
      if (cor[i][1] > 9)
      {
        cor[i][1] = 18 - cor[i][1];
        spd[i][1] = -spd[i][1];
      }
      switch(i)
      {
        case 0:
          setPixel(cor[i][0], cor[i][1], 0xC00000L);
          break;
          case 1:
          setPixel(cor[i][0], cor[i][1], 0x00C000L);
          break;
          case 2:
          setPixel(cor[i][0], cor[i][1], 0x0000C0L);
          break;
      }
    }
    
    delay(100);
    long t = micros();
    pixels.show(); 
    t = micros()-t;
    Serial.println(t);
  }
}




