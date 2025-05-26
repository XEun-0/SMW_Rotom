// Declare globals as extern in this file
// while declaring actually for other files
// that require gDisplayRuntime, gWatchOSRuntime
#define DECLARE_GLOBALS
// Task inclusions
#include "globals.h"

#include "watchController.h"
#include "tester.h"

TouchscreenTester tester;


#define ENABLE_TESTER 1

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
// void printTouchToSerial(int touchX, int touchY, int touchZ) {
//     // Serial.print("X = ");
//     // Serial.print(touchX);
//     // Serial.print(" | Y = ");
//     // Serial.print(touchY);
//     // Serial.print(" | Pressure = ");
//     // Serial.print(touchZ);
//     // Serial.println();
// }

// Print Touchscreen info about X, Y and Pressure (Z) on the TFT Display
void printTouchToDisplay(int touchX, int touchY, int touchZ) {
    // // Clear TFT screen
    // tft.fillScreen(TFT_WHITE);
    // tft.setTextColor(TFT_BLACK, TFT_WHITE);

    // int centerX = SCREEN_WIDTH / 2;
    // int textY = 80;

    // String tempText = "X = " + String(touchX);
    // tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

    // textY += 20;
    // tempText = "Y = " + String(touchY);
    // tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

    // textY += 20;
    // tempText = "Pressure = " + String(touchZ);
    // tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);
}

/*********************************************************
 * 
 * Name:  setup
 * Notes: Arduino way of starting application task
 * 
 *********************************************************/
void setup() {
    Serial.begin(115200);

#ifdef ENABLE_TESTER
    // Run touchscreen test instead of launching RTOS scheduler
    tester.begin();
#else
    // Create main controller task
    xTaskCreate(
        watchControllerTaskLauncher,        // Function to be called
        "watchControllerTaskLauncher",      // Name of the task
        512,                                // Stack size
        NULL,                               // Parameters passed to task
        1,                                  // Task priority (higher number = higher priority)
        NULL                                // Task handle for reference
    );
    
    gDisplayRuntime.DisplayRuntimeTaskLauncher();

    vTaskStartScheduler();
#endif
}

/*********************************************************
 * 
 * Name:  loop
 * Notes: RTOS removes loop functionality
 * 
 *********************************************************/
void loop() {
#ifdef ENABLE_TESTER
    // Loop the tester
    tester.loop();
#endif
}