#include <Colorduino.h>

void setup()
{
  Colorduino.Init(); 
  unsigned char whiteBalVal[3] = {36,63,63}; // for LEDSEE 6x6cm round matrix
  Colorduino.SetWhiteBal(whiteBalVal);
  Colorduino.ColorFill(0,0,0);
}

void setPixels(int lines[], int r, int g, int b)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if ((lines[i]>>j) & 0x01)
      {
          Colorduino.SetPixel(i, j, r,g,b);
      }
      else
      {
        Colorduino.SetPixel(i, j, 0,0,0);
      }
     }
   }
  Colorduino.FlipPage();   
}

int herz[] = {
      0b00000000,
      0b01100110,
      0b11111111,
      0b11111111,
      0b01111110,
      0b01111110,
      0b00111100,
      0b00011000,      
};


int diamant[] = {
      0b00011000,
      0b00100100,
      0b01011010,
      0b10111101,
      0b10111101,
      0b01011010,
      0b00100100,
      0b00011000,      
};

int hund[] = {
      0b00100000,
      0b11100010,
      0b11100001,
      0b00110001,
      0b00111110,
      0b00111110,
      0b01100011,
      0b10100110,      
};

int kreis[] = {
      0b00011000,
      0b01100110,
      0b01000010,
      0b10000001,
      0b10000001,
      0b01000010,
      0b01100110,
      0b00011000,      
};


int smiley[] = {
      0b00111100,
      0b01000010,
      0b10100101,
      0b10000001,
      0b10100101,
      0b10011001,
      0b01000010,
      0b00111100,      
};

int smiley2[] = {
      0b00000000,
      0b00000000,
      0b01000100,
      0b00010000,
      0b00010000,
      0b01000100,
      0b00111000,
      0b00000000,      
};

int katze[] = {
      0b10000010,
      0b11000110,
      0b11111110,
      0b10000010,
      0b10101010,
      0b10010010,
      0b10111010,
      0b01111100,      
};


int kristall[] = {
      0b00000000,
      0b00010000,
      0b00111000,
      0b01111100,
      0b01111100,
      0b00111000,
      0b00010000,
      0b00000000,      
};

int stern[] = {
      0b10010001,
      0b01010110,
      0b00111000,
      0b11111111,
      0b00111000,
      0b01010100,
      0b01010010,
      0b10010001,      
};

int a[] = {
      0b00000000,
      0b00001000,
      0b00010100,
      0b00100010,
      0b00111110,
      0b00100010,
      0b00100010,
      0b00000000,      
};

int n[] = {
      0b00000000,
      0b00100010,
      0b00100010,
      0b00111110,
      0b00100010,
      0b00100010,
      0b00100010,
      0b00000000
};

int ja[] = {
      0b00000000,
      0b00111100,
      0b00100010,
      0b00111100,
      0b00101000,
      0b00100100,
      0b00100010,
      0b00000000
};


void loop()
{
  
  
  setPixels(herz, 255,0,255);
  delay(500);
  
  setPixels(diamant, 0,0,255);
  delay(500);
  
  setPixels(hund, 255,255,0);
  delay(500);
  
  setPixels(kreis, 255,255,0);
  delay(500);
  
  setPixels(smiley,255,0,255);
  delay(1000);
  
  setPixels(smiley2,255,255,0);
  delay(1000);
 
  setPixels(katze,125,125,125);
  delay(1000);
 

  setPixels(kristall, 0,255,0);
  delay(1000);


  setPixels(stern, 150,0,255);
  delay(1000);
  
  setPixels(a, 255,0,150);
  delay(1000);
  setPixels(n, 255,0,150);
  delay(1000);
  setPixels(ja, 255,0,150);
  delay(1000);

}
