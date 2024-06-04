#ifndef WEATHER_H_
#define WEATHER_H_

#include <Adafruit_SSD1306.h>
#include "Menu.h"

// Extern Vars
extern Adafruit_SSD1306 display;
extern int buttonPin;
extern int buttonState;
extern int lastButtonState;
extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;

void setupDHT();
void loopDHT();
void updateDisplay();
void updateTemperatureDisplay();
void updateHumidityDisplay();
void updateSensorData();

#endif