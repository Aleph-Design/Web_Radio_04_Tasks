#if !defined(MAIN_H)
#define MAIN_H

#include <WiFi.h>           // Requires raw HTTP connection
#include <VS1053.h>         // https://github.com/baldram/ESP_VS1053_Library
#include <wifiConfig.h>     // WiFi user settings in ../WiFiSpecs
#include <wireConfig.h>     // Pins used by ESP32
#include <mp3Hello.h>       // An introduction to check the player
//#include <radioStats.h>     // A few radio stations
//#include <connectRadio.h>   // Connect to WiFi etc.
//#include <changeRadio.h>    // Library to handle changing radio stations
#include <tasksConfig.h>    // Configuration for all tasks
#include <createAllTasks.h> // Prototype for the creation of all tasks

// Declare an index to the currently playing radio station. It's defined in
// *.cpp
//
extern uint8_t sIndex;

#endif // MAIN_H
