#ifndef MENU_H_
#define MENU_H_

#include <Adafruit_SSD1306.h>
#include <Encoder.h>

// Extern Vars
extern Adafruit_SSD1306 display;

void setupEncoder();

void loopEncoder();

void displayMenu();

void executeFunction(int selectedItem);

#endif