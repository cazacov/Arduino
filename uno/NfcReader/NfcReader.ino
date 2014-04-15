#include <PN532.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

/*Chip select pin can be connected to D10 or D9 which is hareware optional*/
/*if you the version of NFC Shield from SeeedStudio is v2.0.*/
#define PN532_CS 10
PN532 nfc(PN532_CS);
#define PIN 6

enum Heros
{
   WashBuckler,
   BlastZone,
   Ninja,
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
    else
    {
      hero = Unknown;
    }
    
    switch (hero)
    {
      case WashBuckler:
        color = 0x00002020FFL; // blue      
        Serial.println("Wash Buckler");
        break;
      case BlastZone:
        color = 0x00FF9900L; // orange
        Serial.println("Blast Zone");
        break;
       case Ninja:
        color = 0x0000FF00L; // green
        Serial.println("Ninja Stealth Elf");
        break;        
      default:
        color = 0x00800000L; // dark red      
        Serial.print("Unknown: ");
        Serial.println(id);
        break;
    }
    for (int i = 0; i < 24; i++)
    {
        strip.setPixelColor(i, color);
        strip.show();
        delay(25);
        strip.setPixelColor(i, 0x00000000L);
    }
    strip.show();
  }
}



