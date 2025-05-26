#ifndef GLOBALS_H
#define GLOBALS_H

#include "Hardware/displayRuntime.h"
#include "Hardware/touchRuntime.h"

#include <SPI.h>
// TFT_eSPI
// by Bodmer
#include <TFT_eSPI.h>

// XPT2046_Touchscreen
// by Paul Stoffregen
#include <XPT2046_Touchscreen.h>

// Forward declarations
class DisplayRuntime;
class ToyuchRuntime;

#ifdef DECLARE_GLOBALS

extern DisplayRuntime   gDisplayRuntime;
extern TouchRuntime     gTouchRuntime;

#else

DisplayRuntime  gDisplayRuntime;
TouchRuntime    gTouchRuntime;

#endif

#endif  // GLOBALS_H