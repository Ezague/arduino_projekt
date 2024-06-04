#include "Menu.h"
#include "Clock.h"
#include "weather.h"
#include <Encoder.h>

// Define the pins for the encoder
#define ENCODER_CLK 7
#define ENCODER_DT 6
#define ENCODER_SW 5

int buttonPin = 2; // Button to change different things
int buttonState = LOW;
int lastButtonState = LOW; // Previous state of the button
unsigned long lastDebounceTime = 0; // Last time the button state changed
unsigned long debounceDelay = 50; // Debounce time in milliseconds

Encoder encoder(ENCODER_CLK, ENCODER_DT);

// Variables to store the current position and previous position
long currentPosition = -999;
long previousPosition = -999;

const int menuLength = 2;
String menuItems[menuLength] = {"Clock", "Temp and Humidity"};
int selectedItem = 0;

void setupEncoder()
{
    pinMode(ENCODER_SW, INPUT_PULLUP);

  // Display the initial menu
    //displayMenu();
}

void loopEncoder()
{
  // Read the encoder position
  currentPosition = encoder.read() / 4;

  if (currentPosition != previousPosition) {
    if (currentPosition > previousPosition) {
      // Encoder turned right
      selectedItem++;
      if (selectedItem >= menuLength) {
        selectedItem = 0;
      }
    } else {
      // Encoder turned left
      selectedItem--;
      if (selectedItem < 0) {
        selectedItem = menuLength - 1;
      }
    }
    previousPosition = currentPosition;
    displayMenu();
  }

  // Check if the push button is pressed
  if (digitalRead(ENCODER_SW) == LOW) {
    // Debounce delay
    delay(50);
    if (digitalRead(ENCODER_SW) == LOW) {
      executeFunction(selectedItem);
      // Wait for the button to be released
      while (digitalRead(ENCODER_SW) == LOW);
      // Debounce delay
      delay(50);
    }
  }
}

void displayMenu() {
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setTextSize(1); // Draw 2X-scale text
    display.setCursor(0, 0); // Start at top-left corner
    display.println("Menu:");
    for (int i = 0; i < menuLength; i++) {
        if (i == selectedItem) {
            display.print("> ");
        } else {
            display.print("  ");
        }
        display.println(menuItems[i]);
    }
    display.println();
    display.display();
}

void executeFunction(int item) {
  Serial.print("Executing function for ");
  Serial.println(menuItems[item]);
  // Here, add the functionality you want for each menu item
  switch (item) {
    case 0:
      setupRTC();
      while (true) 
      {
        loopRTC();
      }
      break;
    case 1:
        setupDHT();
        while (true) 
        {
          loopDHT();
        }
      break;
  }
}