#if !defined(CONNECT_RADIO_H)
#define CONNECT_RADIO_H

#include <Arduino.h>
#include <wifiConfig.h>
#include <WiFi.h>
#include <changeRadio.h>

/* 
* If you define the class in an header/include file (*.h file) you make the
* class public. 
* Every other source file that includes this header file will know about the
* class and can e.g. have a pointer to it.
*
* This class is responsable for connecting to WiFiClient and to establish a 
* connection to the HTTP server that provides for a data stream of bytes that
* represents the music playing radio station.
*/
class ConnectRadio
{
  private:
    // @ _curIndex
    // - An index into the array sRadioStation containing structs that contain
    //   radio station data: host, path, port, name, etc.
    //   This is the actual currently playing radio station.
    //
    uint32_t _curIndex;

  public:
	  ConnectRadio(ChangeRadio *pChangeRadio)
    {
      _curIndex = pChangeRadio->getCurrentRadioIndex();
    };

	  ~ConnectRadio();

    // Define WiFiClient wClient public to be used also in task...
    //
    WiFiClient wClient;      

    void connectToWiFi();
    void connectRadioStation();
    uint32_t getConnectedIndex();

};  // end class ConnectRadio

#endif // CONNECT_RADIO_H
