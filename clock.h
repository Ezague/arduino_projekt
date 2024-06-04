#ifndef CLOCK_H_
#define CLOCK_H_

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>

// Extern Vars
extern Adafruit_SSD1306 display;

void setupRTC();
void printDigits(int digits);
void printTime(const DateTime& now);
void printDate(const DateTime& now);
void loopRTC();

#endif