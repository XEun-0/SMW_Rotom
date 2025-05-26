#include "Hardware/displayRuntime.h"

//====== Initialize Variables ============================
TFT_eSPI tft = TFT_eSPI();
//========================================================

/*********************************************************
 * 
 * Name:  DisplayRuntime
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
DisplayRuntime::DisplayRuntime(void) {

}

/*********************************************************
 * 
 * Name:  ~DisplayRuntime
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
DisplayRuntime::~DisplayRuntime(void) {

}

bool DisplayRuntime::isInitialized(void) {
    return true;
}

/*********************************************************
 * 
 * Name:  mainLoop
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
void DisplayRuntime::mainLoop(void) {
    // Do whatever

    //==============
    // // Start the SPI for the touchscreen and init the touchscreen
    // touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    // touchscreen.begin(touchscreenSPI);
    // // Set the Touchscreen rotation in landscape mode
    // // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
    // touchscreen.setRotation(1);

    // check here for if touch sensor is ready before anything else is started for display.

    // or rather it's probably best to put all the checks inside the controller files.
    // keep display related information checking here instead of checking everything. just initialize,
    // display here and write stuff to update the display if needed.
    //==============

    init();    

    while(1) {
        // Do whatever
    }

    // Send error code serial msg if needed.
    vTaskDelete( NULL );
}

/*********************************************************
 * 
 * Name:  init
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
void DisplayRuntime::init(void) {
    // Start the tft display
    tft.init();
    // Set the TFT display rotation in landscape mode
    tft.setRotation(1);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    
    // Set X and Y coordinates for center of display
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    tft.drawCentreString("Hello, world!", centerX, 30, FONT_SIZE);
    tft.drawCentreString("Touch screen to test", centerX, centerY, FONT_SIZE);
}

/*********************************************************
 * 
 * Name:  DisplayRuntimeTaskLauncher
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
void DisplayRuntime::DisplayRuntimeTaskLauncher(void) {
    xTaskCreate(
        processDisplayRuntimeTask,           // Function to be called
        "processDisplayRuntimeTask",         // Name of the task
        512,                            // Stack size
        this,                           // Parameters passed to task
        2,                              // Task priority (higher number = higher priority)
        NULL                            // Task handle for reference
    );
}

/*********************************************************
 * 
 * Name:  processDisplayRuntimeTask
 * Notes: See displayRuntime.h
 * 
 *********************************************************/
void DisplayRuntime::processDisplayRuntimeTask( void *pvParams) {
    // Retrieve the singleton instance of the DisplayRuntime class.
    // This ensures that only one instance of DisplayRuntime exists 
    // and is used throughout the program.

    DisplayRuntime *pDisplayRuntime = static_cast<DisplayRuntime *>(pvParams);
    pDisplayRuntime->mainLoop();
}

// Not in class

