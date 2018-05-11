/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   6
#define MAXCS   7
#define MAXCLK  8

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

Adafruit_24bargraph bar = Adafruit_24bargraph();

// initialize the library with the numbers of the interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
  
void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  lcd.clear();
  lcd.print("MAX31855 test");
  // wait for MAX chip to stabilize
    Serial.begin(9600);
  Serial.println("HT16K33 Bi-Color Bargraph test");
  
  bar.begin(0x70);  // pass in the address

  for (uint8_t b=0; b<24; b++ ){
    if ((b % 3) == 0)  bar.setBar(b, LED_RED);
    if ((b % 3) == 1)  bar.setBar(b, LED_YELLOW);
    if ((b % 3) == 2)  bar.setBar(b, LED_GREEN);
  }
  bar.writeDisplay();
  delay(2000);
}

void loop() {
  // basic readout test, just print the current temp
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Int. Temp = ");
   lcd.println(thermocouple.readInternal());
   Serial.print("Int. Temp = ");
   Serial.println(thermocouple.readInternal());
     
   double c = thermocouple.readCelsius();
   lcd.setCursor(0, 1);
   if (isnan(c)) 
   {
     lcd.print("T/C Problem");
   } 
   else 
   {
    if(c<=25){
      for (uint8_t b=0; b<24; b++) {
        bar.setBar(b, LED_GREEN);
        bar.writeDisplay();
      }
    }

    if(c>25 && c<=30){
      for (uint8_t b=0; b<24; b++) {
        bar.setBar(b, LED_YELLOW);
        bar.writeDisplay();
        if (c=26){
          bar.setBar(0, LED_RED);
          bar.writeDisplay();
        }
        if (c=27){
          bar.setBar(1, LED_RED);
          bar.writeDisplay();
        }
        if (c=28){
          bar.setBar(2, LED_RED);
          bar.writeDisplay();
        }
      }
    }

    if(c>30){
      for (uint8_t b=0; b<24; b++) {
        bar.setBar(b, LED_RED);
        bar.writeDisplay();
      }
    }
     lcd.print("C = "); 
     lcd.print(c);
     lcd.print("  "); 
     Serial.print("Thermocouple Temp = *");
     Serial.println(c);
   }
 
   delay(1000);
}
