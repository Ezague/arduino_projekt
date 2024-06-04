#include <RTClib.h>
#include "Clock.h"

#define DELAY 1000 // Update interval in milliseconds
RTC_DS3231 rtc;
unsigned long previousMillis = 0;
char daysOfTheWeek[7][12] = {"Søndag", "Mandag", "Tirsdag", "Onsdag", "Torsdag", "Fredag", "Lørdag"};

void loopRTC()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= DELAY) {
        previousMillis = currentMillis;

        DateTime now = rtc.now();

        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE); // Draw white text

        display.setTextSize(2); // Draw 2X-scale text
        display.setCursor(0, 0); // Start at top-left corner
        printTime(now);

        display.setTextSize(1); // Normal 1:1 pixel scale
        display.setCursor(0, 30);
        printDate(now);

        display.display();
    }
}

void setupRTC()
{
    #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
#endif

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    } 
}

// Function to start the RTC and print it do the display
void printDigits(int digits) {
    // utility function for digital clock display: prints preceding colon and leading 0
    if (digits < 10)
        display.print('0');
    display.print(digits);
}

void printTime(const DateTime& now) {
    printDigits(now.hour());
    display.print(":");
    printDigits(now.minute());
    display.print(":");
    printDigits(now.second());
    display.println();
}

void printDate(const DateTime& now) {
    display.print(daysOfTheWeek[now.dayOfTheWeek()]);
    display.print(" ");
    printDigits(now.day());
    display.print(".");
    printDigits(now.month());
    display.print(".");
    display.println(now.year(), DEC);
}

