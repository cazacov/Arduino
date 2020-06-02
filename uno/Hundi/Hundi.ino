#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int color = 0x000018;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();
  for (int i = 0; i < 16; i++)
  {
    strip.setPixelColor(i, color);
  }
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int color = 0x000020;
  int idx[][4] = {
    {2,2,14,14}, 
    {1,3,13, 15},
    {0,4,12,8}, 
    {7,5,11, 9},
    {6,6,10, 10}
   };
   
   for (int j = 0; j <5; j++)
   {
     for (int i = 0; i < 4; i++)
     {
       strip.setPixelColor(idx[j][i], 0);
     }
     strip.show();
     delay(50);
   }
   delay(200);
   for (int j = 4; j >=0; j--)
   {
     for (int i = 0; i < 4; i++)
     {
       strip.setPixelColor(idx[j][i], color);
     }
     strip.show();
     delay(60);
   }
   delay(5000);
}

