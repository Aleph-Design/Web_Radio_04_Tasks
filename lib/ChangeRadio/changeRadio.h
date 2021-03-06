#if !defined(CHANGE_RADIO_H)
#define CHANGE_RADIO_H
/*
* This class is responsible for reading the index of the last played radio 
* station from non-volatile storage Preferences. It's also responsable for
* writing this index to NVS. I'm still looking for a solution to write the
* index of the currently playing station only when the ESP32 is switched
* off.
* Next task is to generate indexes with the help of a rotating encoder.
* Each new generated index displays the stations name. We only connect to
* the generated station when the button of the rotary encoder is pressed.
*
* @ curIndex
* - An index into the array sRadioStation containing structs that contain
*   radio station data: host, path, port, name, etc.
*   This is the actual currently playing radio station.
*
* @ encIndex
* - An index generated by the rotary encoder. This index only takes the 
*   station name from the array sRadioStation and displays that.
*   When the button on the rotary encoder is pressed;
*   curIndex = encIndex and and the actual currently playing radio station
*   is pointed to by curIndex.
*/

#include <Preferences.h>


class ChangeRadio
{
  private:
    Preferences *pLocalPrefs;
    uint32_t _curIndex;
    uint32_t _encIndex;   // Do I need it here?

  public:
	  ChangeRadio(Preferences *pGlobalPrefs)
      {
          this->pLocalPrefs = pGlobalPrefs;

          // Open nameSpace "RadioStation" in Non-Volatile Storage Preferences
          //
          pGlobalPrefs->begin("RadioStation", false);

          // Get the stored value for key: "prevRadio"
          //
          _curIndex = pGlobalPrefs->getUInt("prevRadio", 0);

          Serial.printf("\nRadio Station index from Preferences: %d\n", _curIndex);

      } // end constructor ChangeRadio()

	  ~ChangeRadio(){};

      uint32_t getCurrentRadioIndex();

      void setCurrentRadioIndex(uint32_t encIndex);

      void storeCurrentRadioIndex();

      void preferencesClose();

};  // end class ChangeRadio


#endif // CHANGE_RADIO_H
