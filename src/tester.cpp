#include "tester.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

// These are declared elsewhere and linked in (globals or runtime files)
extern TFT_eSPI tft;
extern SPIClass touchscreenSPI;
extern XPT2046_Touchscreen touchscreen;

void TouchscreenTester::begin() {
    Serial.println("Starting touchscreen tester...");

    // Re-init touchscreen SPI (just in case)
    touchscreenSPI.begin(25, 39, 32, 33); // CLK, MISO, MOSI, CS
    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(1); // Landscape

    tft.init();
    tft.setRotation(1); // Landscape
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    tft.drawCentreString("Hello, world!", centerX, 30, fontSize);
    tft.drawCentreString("Touch screen to test", centerX, centerY, fontSize);
}

void TouchscreenTester::loop() {
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();

        int x = map(p.x, 200, 3700, 1, screenWidth);
        int y = map(p.y, 240, 3800, 1, screenHeight);
        int z = p.z;

        printTouchToSerial(x, y, z);
        printTouchToDisplay(x, y, z);

        delay(100);
    }
}

void TouchscreenTester::printTouchToSerial(int x, int y, int z) {
    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();
}

void TouchscreenTester::printTouchToDisplay(int x, int y, int z) {
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    int centerX = screenWidth / 2;
    int textY = 80;

    tft.drawCentreString("X = " + String(x), centerX, textY, fontSize);
    textY += 20;
    tft.drawCentreString("Y = " + String(y), centerX, textY, fontSize);
    textY += 20;
    tft.drawCentreString("Pressure = " + String(z), centerX, textY, fontSize);
}
