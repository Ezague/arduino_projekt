#include "weather.h"
#include <DHT.h>

#define DHTPIN 10
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
    dht.begin();
}

void loopDHT() {
    display.clearDisplay();

    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("DHT22 Sensor");
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.print("Temp: ");
    display.print(temp);
    display.println(" C");
    display.setCursor(0, 30);
    display.print("Humidity: ");
    display.print(humidity);
    display.println(" %");
    display.display();
    delay(6000);
}