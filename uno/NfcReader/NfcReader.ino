#include <PN532.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

/*Chip select pin can be connected to D10 or D9 which is hareware optional*/
/*if you the version of NFC Shield from SeeedStudio is  v2.0.*/
#define PN532_CS 10
PN532 nfc(PN532_CS);
#define PIN 6

enum Heros
{
   WashBuckler,
   BlastZone,
   Ninja,
   Bob,
   Alice,
   Unknown
} hero = Unknown;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

void setup(void) {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
  Serial.println("Hello!");
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
  
  for (int i = 0; i < 24; i++)
  {
    strip.setPixelColor(i, 0x00002000);
    strip.show();
    delay(25);
  }
  for (int i = 0; i < 24; i++)
  {
    strip.setPixelColor(i, 0x00000000L);
    strip.show();
    delay(25);
  }
}


void loop(void) {
  uint32_t id;
  // look for MiFare type cards
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
  
  
  
  if (id != 0) {
    long color = 0;
    
    if (id == 3207720708 || id == 816892589)
    {
      hero = WashBuckler;
    }
    else if (id == 3562341356 || id == 2060644139)
    {
      hero = BlastZone;
    }
    else if (id == 3747222318)
    {
      hero = Ninja;
    }
    else if (id == 1293218043)
    {
      hero = Bob;
    }
    else if (id == 498266107)
    {
      hero = Alice;
    }
    else
    {
      hero = Unknown;
    }
    
    switch (hero)
    {
      case WashBuckler:
        color = 0x00FF0000L; // blue      
        Serial.println("Wash Buckler");
        break;
      case BlastZone:
        color = 0x00FF0000L; // orange
        Serial.println("Blast Zone");
        break;
       case Ninja:
        color = 0x00FF0000L; // green
        Serial.println("Ninja Stealth Elf");
        break;        
      case Bob:
        color = 0x00000000FFL; // blue      
        Serial.println("BOB - Kaffee");
        break;
      case Alice:
        color = 0x0000FF0040L; // blue      
        Serial.println("Alice - Cappuccino");
        break;
      default:
        color = 0x00800000L; // dark red      
        Serial.print("Unknown");
        Serial.println(id);
        break;
    }
    delay(200);
    for (int i = 0; i < 24 + 8; i++)
    {
        for (int j = 0; j < 24; j++)
        {
          if (j > i)
          {
            continue;
          }
          if (i - j > 8)
          {
            strip.setPixelColor(j, 0x00000000L);
          }
          else {
            long r = (color & 0x00FF0000L) >> 16;
            long g = (color & 0x0000FF00L) >> 8;
            long b = (color & 0x000000FFL);
            r = (r * (8 - i + j)) >> 3;
            g = (g * (8 - i + j)) >> 3;
            b = (b * (8 - i + j)) >> 3;
            strip.setPixelColor(j, (r << 16) + (g << 8) + b);
          }
       }
       strip.show();
       delay(25);
    }
    strip.show();
    delay(2000);
  }
}



