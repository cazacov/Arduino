// Example of using SainSmart IIC/I2C/TWI Serial 2004 20x4 LCD Module
// For the Arduino 
// UNO: SDA - A4, SCL - A5. 
// Leonardo: SDA - D2, SCL - D3
// Mega 2560: SDA - 20, SCL - 21
// DUE: SDA - 20, SCL - 21 over 3.3 <-> 5V level converter


// LCD Library: https://arduino-info.wikispaces.com/file/detail/LiquidCrystal_I2C2004V1.zip

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Addr: 0x3F, 20 chars & 4 lines
LiquidCrystal_I2C lcd(0x3F,20,4); 

void setup()
{
    lcd.init(); 
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello");
    lcd.setCursor(0, 1);
    lcd.print("World!");

}
void loop()
{

}
