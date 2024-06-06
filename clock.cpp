#include <RTClib.h>
#include "Clock.h"

#define DELAY 1000 // Update interval in milliseconds
RTC_DS3231 rtc;
unsigned long previousMillis = 0;

struct Locale {
    const char *daysOfTheWeek[7];
    const char *dateFormat;
};

Locale locales[] = {
    {
        {"Søndag", "Mandag", "Tirsdag", "Onsdag", "Torsdag", "Fredag", "Lørdag"},
        "DD.MM.YYYY"
    },
    {
        {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
        "MM/DD/YYYY"
    },
};

const char *timeZones[] = {
    "DK", // Central European Time
    "US"  // Greenwich Mean Time
};

int currentLocale = 0; // Default locale
bool use12HourFormat = false; // Default to 24-hour format
int currentTimeZone = 0; // Default time zone

void setupRTC() {
#ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
#endif

    pinMode(buttonPin, INPUT);
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

void loopRTC() {
    int reading = digitalRead(buttonPin);

    if (reading != lastButtonState) {
        lastDebounceTime = millis(); // Reset the debouncing timer
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == HIGH) {
                currentLocale = (currentLocale + 1) % (sizeof(locales) / sizeof(locales[0]));
                use12HourFormat = !use12HourFormat; // Toggle between 12-hour and 24-hour formats
                // Toggle between time zones
                currentTimeZone = (currentTimeZone + 1) % (sizeof(timeZones) / sizeof(timeZones[0]));

                // Update display immediately after changing the format
                DateTime now = rtc.now();
                display.clearDisplay();
                display.setTextColor(SSD1306_WHITE); // Draw white text

                display.setTextSize(2); // Draw 2X-scale text
                display.setCursor(0, 0); // Start at top-left corner
                printTime(now);

                display.setTextSize(1); // Normal 1:1 pixel scale
                display.setCursor(0, 30);
                printDate(now);

                display.setTextSize(1); // Normal 1:1 pixel scale
                display.setCursor(0, 50);
                display.print("Format: ");
                display.println(timeZones[currentTimeZone]);

                display.display();
            }
        }
    }

    lastButtonState = reading;

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

        display.setTextSize(1); // Normal 1:1 pixel scale
        display.setCursor(0, 50);
        display.print("Format: ");
        display.println(timeZones[currentTimeZone]);

        display.display();
    }
}

void printDigits(int digits) {
    // Utility function for digital clock display: prints preceding colon and leading 0
    if (digits < 10)
        display.print('0');
    display.print(digits);
}

void printTime(const DateTime& now) {
    if (use12HourFormat) {
        int hour = now.hour() % 12;
        if (hour == 0) hour = 12; // Convert 0 to 12 for 12-hour format
        printDigits(hour);
    } else {
        printDigits(now.hour());
    }
    display.print(":");
    printDigits(now.minute());
    display.print(":");
    printDigits(now.second());
    if (use12HourFormat) {
        display.print(now.hour() < 12 ? "AM" : "PM");
    }
    display.println();
}

void printDate(const DateTime& now) {
    Locale locale = locales[currentLocale];

    display.print(locale.daysOfTheWeek[now.dayOfTheWeek()]);
    display.print(" ");

    char buffer[11];
    if (strcmp(locale.dateFormat, "DD.MM.YYYY") == 0) {
        sprintf(buffer, "%02d.%02d.%04d", now.day(), now.month(), now.year());
    } else if (strcmp(locale.dateFormat, "MM/DD/YYYY") == 0) {
        sprintf(buffer, "%02d/%02d/%04d", now.month(), now.day(), now.year());
    }

    display.println(buffer);
}
