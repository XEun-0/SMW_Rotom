#ifndef DISPLAY_RUNTIME
#define DISPLAY_RUNTIME

#include <Arduino.h>
#include <Hardware/displayInterface.h>

class DisplayRuntime {

public:
    // Constuctor / Destructor
    DisplayRuntime(void);
    ~DisplayRuntime(void);

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
     * Name:  DisplayRuntimeTaskLauncher
     * Notes: ...
     * 
     *********************************************************/
    void DisplayRuntimeTaskLauncher();

    /*********************************************************
     * 
     * Name:  isInitialized
     * Notes: n/a
     * 
     *********************************************************/
    bool isInitialized(void);

private:
    //====== Initialize Variables ============================
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
     * Name:  processDisplayRuntimeTask
     * Notes: create static instance if it doesn't exist
     * 
     *********************************************************/
    static void processDisplayRuntimeTask( void *pvParams );
};

// Not in class

#endif // DISPLAY_RUNTIME