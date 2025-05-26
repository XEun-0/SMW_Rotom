#include "watchController.h"

//====== Initialize Variables ============================

WatchController *WatchController::instance = nullptr;

//========================================================

/*********************************************************
 * 
 * Name:  WatchController
 * Notes: See watchController.h
 * 
 *********************************************************/
WatchController::WatchController(void) {

}

/*********************************************************
 * 
 * Name:  ~WatchController
 * Notes: See watchController.h
 * 
 *********************************************************/
WatchController::~WatchController(void) {

}

/*********************************************************
 * 
 * Name:  init
 * Notes: See watchController.h
 * 
 *********************************************************/
void WatchController::init(void) {
    bool test = gDisplayRuntime.isInitialized();
}

/*********************************************************
 * 
 * Name:  mainLoop
 * Notes: See watchController.h
 * 
 *********************************************************/
void WatchController::mainLoop(void) {
    // Do whatever

    while(1) {
        // Do whatever
    }

    // Send error code serial msg if needed.
    vTaskDelete( NULL );
}

/*********************************************************
 * 
 * Name:  getInstance
 * Notes: See watchController.h
 * 
 *********************************************************/
WatchController *WatchController::getInstance (void) {
    if (WatchController::instance == nullptr) {
        WatchController::instance = new WatchController();
        WatchController::instance->init(); // may not be needed
    }

    return WatchController::instance;
}

/*********************************************************
 * 
 * Name:  watchControllerTaskLauncher
 * Notes: See watchController.h
 * 
 *********************************************************/
void watchControllerTaskLauncher( void *pvParams ) {
    // Retrieve the singleton instance of the WatchController class.
    // This ensures that only one instance of WatchController exists 
    // and is used throughout the program.

    WatchController *pWatchController = WatchController::getInstance();
    pWatchController->mainLoop();
}

// Not in class