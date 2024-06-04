#ifndef CLOCK_H_
#define CLOCK_H_

#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <RTClib.h>
#include "Menu.h"

// Extern Vars
extern Adafruit_SSD1306 display;
extern int buttonPin;
extern int buttonState;
extern int lastButtonState;
extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;

void setupRTC();
void printDigits(int digits);
void printTime(const DateTime& now);
void printDate(const DateTime& now);
void loopRTC();

#endif