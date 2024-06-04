#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include "Clock.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define I2C_ADDRESS 0x3C // I2C address for the OLED display
#define DELAY 2000 // Update interval in milliseconds

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(57600);
    setupRTC();

    if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS)) { // Correct I2C Address for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.display();
}

void loop() {
    loopRTC();
}
