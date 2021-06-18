/*
* Pin connections to ESP32 GPIO are according to:
* ~/PlatformIO/WS_WebRadio/common/doc/Bedrading-00
*
* Jan H. Kila van Zuijlen; 26-03-2021
*/
#if !defined(WIRE_CONFIG_H)
#define WIRE_CONFIG_H
/*
* Give this custom library access to the standard 
* Arduino library features.
*/
#include <Arduino.h>

#define VS1053_DREQ 35	// (GPIO35)
#define VS1053_XDCS 32	// (GPIO32)	Data command control pin
#define VS1053_XCS  33	// (GPIO33)	Chip select control pin
#define VS1053_SCK  18	// (GPIO18)	Clock signal
#define VS1053_MISO 19	// (GPIO19)
#define VS1053_XRST 03	// (GPIO03) RXD!!
#define VS1053_MOSI 23	// (GPIO23)

#define TFT_MOSI 23		// (GPIO23)
#define TFT_MISO 19		// (GPIO19)
#define TFT_SCLK 18		// (GPIO18)	Clock signal
#define TFT_CS   08  	// (GPIO08) Chip select control pin
#define TFT_DC   04  	// (GPIO04) Data Command control pin
#define TFT_RST  03  	// (GPIO03) Reset pin (could connect to RST pin)

// Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
//#define TFT_RST  -1  

#define TOUCH_CS  21    // (GPIO21) Chip select pin (T_CS) of touch screen
#define TOUCH_IRQ 39	// (GPIO39)	Interrupt request
#define TOUCH_DO  19	// (GPIO19) MISO
#define TOUCH_DIN 23	// (GPIO23) MOSI

#define VOLUME    85    // volume level 0-100

#define CODER_SW  14    // GPIO 14 on ESP32 [GPIO 34 has no internal PULLUP]
#define CODER_CLK 26    // GPIO 26 on ESP32
#define CODER_DT  27    // GPIO 27 on ESP32

#define GREEN_LED 04
#define RED_LED   10

#endif // WIRECONFIG_H
