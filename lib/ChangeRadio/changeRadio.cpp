/*
* Uses non-volatile storage Preferences.
* The structure is: preferenceStorage < nameSpace < key-value pairs.
* preferenceStorage contains multiple nameSpaces, which in turn contain
* multiple key-value pairs.
* https://www.tutorialspoint.com/esp32_for_iot/esp32_for_iot_preferences.htm
*
* Autor: Jan H. Kila van Zuijlen; 4-6-2021
*/
#include <Arduino.h>
#include <changeRadio.h>
/*
* All methods here must be encoded with the prefix "WiFiConfig::"
* ===============================================================
*
* Within the constructor initialize private variable for settings.
* They are loaded in memory when the library is loaded.
*
* Open Preferences with my-app namespace. Each application module, library, 
* etc. has to use a namespace name to prevent key name collisions. We will 
* open storage in RW-mode (second parameter has to be false).
* Note: Namespace name is limited to 15 chars.
* preferences.begin("my−app", false);
*/

// Get the index of the currently playing radio station.
//
uint32_t ChangeRadio::getCurrentRadioIndex()
{
    Serial.printf("\n2. getCurrentRadioIndex: %d\n", _curIndex);
   return _curIndex;
}

// After pressing the rotary encoder button; set the present encoder index
// as the currently playing radio station index.
// After having done this; connect to the now current playing radio station.
//
void ChangeRadio::setCurrentRadioIndex(uint32_t encIndex)
{
    Serial.printf("\n4. setCurrentRadioIndex: %d\n", encIndex);
    _curIndex = encIndex;
}


// Store the currently playing radio station's index in NVS-preferences
//
void ChangeRadio::storeCurrentRadioIndex()
{
    Serial.printf("\n5. storeCurrentRadioIndex: %d\n", _curIndex);
    pLocalPrefs->putUInt("prevRadio", _curIndex);
}


void ChangeRadio::preferencesClose()
{
    pLocalPrefs->end(); 
}

