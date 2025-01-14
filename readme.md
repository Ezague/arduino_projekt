# Arduino menu for the 128x64 OLED display with SSD1306 driver

### Table of contents
1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Board layout](#board-layout)
4. [Software](#software)
5. [Installation](#installation)
6. [Dependencies](#dependencies)
7. [Usage](#usage)
8. [Author](#author)
9. [License](#license)

### Introduction
* This is a simple Arduino menu for the 128x64 OLED display with the SSD1306 driver. The menu is controlled with a rotary encoder with push button. The menu is drawn with the Adafruit GFX library and the Adafruit SSD1306 library.

### Hardware
* Arduino Zero
* 128x64 OLED display with SSD1306 driver
* Rotary encoder with push button
* DHT11 temperature and humidity sensor

### Board layout
* The Rotary encoder is connected to the Arduino Zero as follows:
  * CLK -> Pin 7
  * DT -> Pin 6
  * SW -> Pin 5
  * VCC -> 3.3V
  * GND -> GND

* The OLED display is connected to the Arduino Zero as follows: (This varies based on Arduino version)
    * SDA -> SDA
    * SCL -> SCL
    * VCC -> 3.3V
    * GND -> GND

* The DHT11 temperature and humidity sensor is connected to the Arduino Zero as follows:
  * DATA -> Pin 10
  * VCC -> 3.3V
  * GND -> GND

### Software
* The software is split into multiple files to maintain a clear structure. The main file is `afslut_opgave.ino`, the menu is defined in `menu.h`, the clock is defined in `clock.h`, and the temperature and humidity sensor is defined in `weather.h`.

### Installation
* To install the software, download the files and open `afslut_opgave.ino` in the Arduino IDE or your preferred editor. Then upload the code to the Arduino Zero.

### Dependencies
* The following libraries are required to run the software:
  * Adafruit SSD1306 library (Used for the OLED display)
  * DHT sensor library (Used for the DHT11 temperature and humidity sensor)
  * Encoder library (Used for the rotary encoder)
  * RTC library (Used for the real-time clock)

### Usage
* The menu is controlled with the rotary encoder. The push button is used to select an item in the menu. The menu items are:
  * Clock (Can be set to 12 or 24 hour format)
  * Weather (Displays the current temperature and humidity)

* The clock displays the current time and date. The weather displays the current temperature and humidity.

### Author
* This project was created by [Sander Petersen](https://github.com/Ezague) in 2024.

### License
* This project is licensed under the MIT License.