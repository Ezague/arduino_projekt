#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Menu.h"
#include "Clock.h"
#include <Wire.h>

#define I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  Serial.begin(57600);
  //setupRTC();
  setupEncoder();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS)) { // Correct I2C Address for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }

  display.clearDisplay();
  display.display();
}

void loop()
{
  // menu for selecting the different functions with rotary encoder
  //loopRTC();
  loopEncoder();
  display.clearDisplay();
}