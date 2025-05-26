#include <SPI.h>
// TFT_eSPI
// by Bodmer
#include <TFT_eSPI.h>

// XPT2046_Touchscreen
// by Paul Stoffregen
#include <XPT2046_Touchscreen.h>

// TFT pinouts
// SDO (MISO) 	GPIO 12
// LED        	GPIO 21
// SCK        	GPIO 14
// SDI (MOSI) 	GPIO 13
// D/C        	GPIO 2
// RESET      	GPIO EN/RESET
// CS         	GPIO 15
// GND        	GPIO GND
// VCC        	5V (or 3.3V)

// TFT Touchscreen pins
#define XPT2046_IRQ 	36   	// T_IRQ
#define XPT2046_MOSI 	32  	// T_DIN
#define XPT2046_MISO 	39  	// T_OUT
#define XPT2046_CLK 	25   	// T_CLK
#define XPT2046_CS 		33    	// T_CS

#define SCREEN_WIDTH    320     // Width in pixels
#define SCREEN_HEIGHT   240     // Height in pixels
#define FONT_SIZE       2       // Font size

// TFT and touchscreen externals
extern TFT_eSPI tft;                        // Declared in displayRuntime.cp
extern SPIClass touchscreenSPI;             // Declared in touchRuntime.h
extern XPT2046_Touchscreen touchscreen;     // Declared in touchRuntime.h