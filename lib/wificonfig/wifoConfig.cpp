/*
* Here you MUST match the includes in the header file
*/
#include <Arduino.h>
#include <wifiConfig.h>

/*
* All methods here must be encoded with the prefix
* "WiFiConfig::"
*
* Within the constructor we initialize private variable
* for our WiFi-settings. They are loaded in memory when
* the library WiFiConfig is loaded.
*/
WiFiConfig::WiFiConfig()
{
	_ssid = (char *)"H369AAF9760";
	_pass = (char *)"A6CD999DC538";
}

/*
* Destructor - resets the private variables when the
* library is unloaded from memory.
*/
WiFiConfig::~WiFiConfig()
{
	_ssid = (char *)"";
	_pass = (char *)"";
}

/*
* Returns the SSID
*/
char *WiFiConfig::ssid()
{
	return _ssid;
}

/*
* Returns the password
*/
char *WiFiConfig::pass()
{
	return _pass;
}