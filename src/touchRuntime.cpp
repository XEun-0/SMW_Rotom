#include "Hardware/touchRuntime.h"

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

TouchRuntime::TouchRuntime(void) {

}

TouchRuntime::~TouchRuntime(void) {

}

/*********************************************************
 * 
 * Name:  mainLoop
 * Notes: ...
 * 
 *********************************************************/
void TouchRuntime::mainLoop(void) {
    // Move to main loop
    SPIClass touchscreenSPI;
    XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

    // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
        // Get Touchscreen points
        TS_Point p = touchscreen.getPoint();
        // Calibrate Touchscreen points with map function to the correct width and height
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        z = p.z;

        // printTouchToSerial(x, y, z);
        // printTouchToDisplay(x, y, z);

        delay(50);
    }
}

/*********************************************************
 * 
 * Name:  TouchRuntimeTaskLauncher
 * Notes: ...
 * 
 *********************************************************/
void TouchRuntime::TouchRuntimeTaskLauncher() {

}

/*********************************************************
 * 
 * Name:  isInitialized
 * Notes: n/a
 * 
 *********************************************************/
bool TouchRuntime::isInitialized(void) {
    return true;
}

/*********************************************************
 * 
 * Name:  init
 * Notes: ...
 * 
 *********************************************************/
void TouchRuntime::init(void) {
    SPIClass touchscreenSPI = SPIClass(VSPI);
    XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
    
    // Touchscreen coordinates: (x, y) and pressure (z)
    
    // Serial.print("X = ");
    // Serial.print(touchX);
    // Serial.print(" | Y = ");
    // Serial.print(touchY);
    // Serial.print(" | Pressure = ");
    // Serial.print(touchZ);
    // Serial.println();
}

/*********************************************************
 * 
 * Name:  processTouchRuntimeTask
 * Notes: create static instance if it doesn't exist
 * 
 *********************************************************/
void TouchRuntime::processTouchRuntimeTask( void *pvParams ) {

}
