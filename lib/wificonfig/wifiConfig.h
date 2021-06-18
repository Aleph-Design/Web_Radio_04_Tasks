/*
* To deploy this library to the Arduino IDE:
*	- Close all open Arduino IDE windows.
*	- Make sure the WiFiConfig directory is located in
*	  /Users/janhkila/Documenten/Arduino/Libraries/
*	- Open up the Arduino IDE
*
* Jan H. Kila van Zuijlen 25-03-2021
*/
#if !defined(WIFI_CONFIG_H)
#define WIFI_CONFIG_H
/*
* Give this custom library access to the standard 
* Arduino library features.
*/
#include <Arduino.h>	

/*
* Users of this library refer to this "class name" 
* when using this custom library
*/
class WiFiConfig
{
public:
	WiFiConfig();
	~WiFiConfig();

	char *ssid();
	char *pass();

private:
	char *_ssid;
	char *_pass;	
};

#endif // WIFI_CONFIG_H