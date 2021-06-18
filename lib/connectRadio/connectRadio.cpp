#include <Arduino.h>
#include <connectRadio.h>
#include <radioStats.h>


void ConnectRadio::connectToWiFi()
{
  // Get WiFi credentials. Keep them local so there's no scattering all
  // over the place!
  //
  WiFiConfig wifiConfig;
  const char *ssid = wifiConfig.ssid();   
  const char *pass = wifiConfig.pass();
 
  Serial.printf("\nConnect to SSID: %s\n", ssid);

  // Start the actual connection
  //
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) 
  {
    // You may choose to blink an LED
    //
    //digitalWrite(redLED, digitalRead(redLED) ^ 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
  }

  Serial.println("\n========================================");
  Serial.print("WiFi connected to IPaddress: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

} // end connectToWiFi() -----------------------------------------------------



void ConnectRadio::connectRadioStation()
{
  RadioStation *pRadio = &sRadioStation[ConnectRadio::getConnectedIndex()];

  Serial.printf("\nConnecting to host: %s\n", pRadio->host);

  if (wClient.connect(pRadio->host, pRadio->port))
  {
    printf("Connect to host: \"%s\" at port: \"%d\" OK!\n\n", 
                        pRadio->host, pRadio->port);
  } else {
    // for (;;)
    // {
    //   digitalWrite(redLED, digitalRead(redLED) ^ 1);
    //   vTaskDelay(300 / portTICK_PERIOD_MS);
    // }
    Serial.println(">>> Connection failed!");
    return;       
  }

  // Show the requested path
  Serial.printf("Requested path: %s\n", pRadio->path);
  Serial.println("Send the request to the server: \n");

  /*
  * For the request we have TWO flavors: One WITHOUT the header for meta data
  * ==========================================================================
  * The difference between these two is in the path.
  * For a path like this "/"; use this request.
  * There's no value for the meta interval, we cannot extract song information
  * from the stream.
  */
  wClient.print(String("GET ") + pRadio->path + " HTTP/1.1\r\n" +
  "Host: " + pRadio->host + "\r\n" + 
  "Connection: close\r\n\r\n"); 
  /*  
  * One WITH the meta data header.
  * ==============================
  * For a path like "/ert-kosmos" use this one:
  *   
  wClient.print(String("GET ") + path[station_no] + " HTTP/1.1\r\n" +
                 "Host: " + host[station_no] + "\r\n" +
                 "Icy-MetaData: 1\r\n" +
                 "Connection: close\r\n\r\n");
                 
  * Here we can extract a value for the meta interval from the header.
  * And therefore we can extract song information from the stream.
  */

  // Wait for the connection to establish
  // const TickType_t xSeconds = pdMS_TO_TICKS(5000);
  //
  Serial.print("\nWait for the connection to establish:\n");
  unsigned long timeout = millis();
  while (wClient.available() == 0) 
  {
    Serial.print(".");
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> wClient timed out after 5 seconds!");
      wClient.stop();
      return;
    }
  }  

  Serial.println("\n\nPermanently read stream data from the server\n"); 

} // end connectToRadioStation() ---------------------------------------------


// The connected index is pointing to the currently playing radio station. The
// variable '_curIndex' is set in class ChangeRadio.
//
uint32_t ConnectRadio::getConnectedIndex()
{
  Serial.printf("\nCurrently playing radio station: %d\n", _curIndex);
  return _curIndex;
}
