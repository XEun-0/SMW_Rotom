#ifndef WATCH_OS_RUNTIME
#define WATCH_OS_RUNTIME

#include <Arduino.h>
#include "Hardware/displayRuntime.h"
#include "globals.h"

class WatchController {

public:
    //====== Initialize Variables ============================
    //========================================================

    /*********************************************************
     * 
     * Name:  getInstance
     * Notes: get singleton instance of the controller
     * 
     *********************************************************/
    static WatchController *getInstance (void);

    /*********************************************************
     * 
     * Name:  mainLoop
     * Notes: ...
     * 
     *********************************************************/
    void mainLoop(void);

    /*********************************************************
     * 
     * Name:  OSRuntimeTaskLauncher
     * Notes: ...
     * 
     *********************************************************/
    void OSRuntimeTaskLauncher();

private:
    //====== Initialize Variables ============================
    static WatchController *instance;
    //========================================================

    /*********************************************************
     * 
     * Name:  WatchController
     * Notes: Constructor
     * 
     *********************************************************/
    WatchController(void);

    /*********************************************************
     * 
     * Name:  ~WatchController
     * Notes: Destructor
     * 
     *********************************************************/
    ~WatchController(void);

    /*********************************************************
     * 
     * Name:  init
     * Notes: ...
     * 
     *********************************************************/
    void init(void);
};

// Not in class

/*********************************************************
 * 
 * Name:  watchControllerTaskLauncher
 * Notes: Makes isntance of WatchController if it doesn't exist
 *        and starts the setup then main loop.
 * 
 *********************************************************/
void watchControllerTaskLauncher( void *pvParams );

#endif // WATCH_OS_RUNTIME