#ifndef TOUCH_RUNTIME
#define TOUCH_RUNTIME

#include <Arduino.h>
#include "Hardware/displayInterface.h"

class TouchRuntime {

public:
    // Constuctor / Destructor
    TouchRuntime(void);
    ~TouchRuntime(void);

    //====== Initialize Variables ============================
    //========================================================

    /*********************************************************
     * 
     * Name:  mainLoop
     * Notes: ...
     * 
     *********************************************************/
    void mainLoop(void);

    /*********************************************************
     * 
     * Name:  TouchRuntimeTaskLauncher
     * Notes: ...
     * 
     *********************************************************/
    void TouchRuntimeTaskLauncher();

    /*********************************************************
     * 
     * Name:  isInitialized
     * Notes: n/a
     * 
     *********************************************************/
    bool isInitialized(void);

private:
    //====== Initialize Variables ============================
    int x, y, z;
    //========================================================

    /*********************************************************
     * 
     * Name:  init
     * Notes: ...
     * 
     *********************************************************/
    void init(void);

    /*********************************************************
     * 
     * Name:  processTouchRuntimeTask
     * Notes: create static instance if it doesn't exist
     * 
     *********************************************************/
    static void processTouchRuntimeTask( void *pvParams );
};

// Not in class

#endif // TOUCH_RUNTIME