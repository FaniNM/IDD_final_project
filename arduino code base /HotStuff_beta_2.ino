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
#define MAXDO   7
#define MAXCS   6
#define MAXCLK  5
int led = 2;
int led1 = 3;
int led2 = 4;
// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

Adafruit_24bargraph bar = Adafruit_24bargraph();



#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
  
void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  delay(20);
  Serial.begin(9600);

  pinMode(led, OUTPUT);   
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  digitalWrite(led, LOW);  
  digitalWrite(led1, LOW);
  digitalWrite(led2 , LOW);  
}

void loop() {
 
   Serial.print("Int. Temp = ");
   Serial.println(thermocouple.readInternal());
     
   double c = thermocouple.readCelsius();
   if (isnan(c)) 
   {
      Serial.print("T/C Problem");
   } 
   else 
   {
    if(c<=25){
      digitalWrite(led, LOW);  
      digitalWrite(led1, LOW);
      digitalWrite(led2 , HIGH);     
      //delay(2000); 
      }

    if(c>25 && c<=30){
      digitalWrite(led, HIGH);
      digitalWrite(led1,LOW);   
      digitalWrite(led2 , LOW); 
      //delay(2000);
    }

    if(c>30){
      digitalWrite(led, LOW); 
      digitalWrite(led1,HIGH); 
      digitalWrite(led2 , HIGH);
      //delay(2000); 
    }
     Serial.print("Thermocouple Temp = *");
     Serial.println(c);
  }
}
