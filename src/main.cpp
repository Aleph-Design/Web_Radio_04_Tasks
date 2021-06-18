/*
* This fourth step is an extension of project: Web_Radio_02
* In Web_Radio_01 we added the circular buffer. 
* See: cBuf_test_00 for a demo project in Xcode.
* We're still not concerned about extracting metaData. 
* Here we add a mechanism to select radio stations.
* We do that by using a separate library: <changeRadio.h>
* 
* Jan H. Kila van Zuijlen; 26-4-2021
* 
*/
#include <Arduino.h>
#include <Preferences.h>
#include <changeRadio.h>
#include <connectRadio.h>
#include <createAllTasks.h>

// In this buffer we receive the Internet stream in chunks of 100 bytes.
//
//char readBuffer[100] __attribute__((aligned(4)));

// The dedicated 32-byte buffer on the VS1053 is aligned on a 4-byte 
// boundary for efficiency.
// The keyword "__attribute__" allows us to specify special attributes 
// of variables or structure fields. This causes the compiler to allocate
// [memory for the variable VS1053_Buff] on a 4-byte boundary.
// The addition: "__attribute__((aligned(4))" forces the compiler to 
// allocate memory for the variable "VS1053_Buff" on a boundary of 32-bits. 
// By doing this, memory reading and writing is very efficient. 
// That is because it takes only one processor cycle on a 32-bit system 
// [as the ESP32 is] to read from or write to memory.
//
//uint8_t VS1053_Buff[32] __attribute__((aligned(4)));

/*
* Global references to libraries / queues
* =======================================
*/
Preferences preferences;      // Create instance of class Preferences
ChangeRadio *pChangeRadio;    // Declare pointer to type: class ChangeRadio

//VS1053 player(VS1053_XCS, VS1053_XDCS, VS1053_DREQ);

/*
* ============================================================================
*   SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP 
* ============================================================================
*/
void setup() 
{
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);	// Stabilize serial

  Serial.printf("\nFree heap: %d\n", ESP.getFreeHeap());

  // Assign the ADDRESS of the instance of class ChangeRadio to the pointer; 
  // NOW pointer 'pChangeRadio' is actually pointing to the instance of class 
  // ChangeRadio. The VALUE of pChangeRadio [*pChangeRadio] is now the address
  // of the instance of ChangeRadio [changeRadio].
  //
  pChangeRadio = new ChangeRadio(&preferences);

  //SPI.begin();                    // initialize SPI bus VS1053
  //initMP3Decoder();

  /*
   * Connecting to the WiFi network the and HTTP server
   * ==================================================
  */
  ConnectRadio *pConnectRadio;  // Declare pointer to type: class ConnectRadio
  pConnectRadio = new ConnectRadio(pChangeRadio);

  pConnectRadio->connectToWiFi();

  pConnectRadio->connectRadioStation();

  // Here we create all tasks in their particular order!
  //
  createAllTasks(pConnectRadio);
  
} // setup() -----------------------------------------------------------------



/*
* ============================================================================
*   LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP
* ============================================================================
*/
void loop() 
{      
} // loop() -----------------------------------------------------------------   



// void initMP3Decoder()
// {
//   player.begin();
//   player.switchToMp3Mode(); // optional; some boards require this
//   player.setVolume(VOLUME);
// }



// /*
// * This should become the function that receives from the Queue.
// * ============================================================================
// */
// void playMusicFromBuffer(void)
// {
// 	bool canPlayMusic = true;
// 	// 
// 	// if (circBuffer.available() >= 32)
// 	// {
// 		if (player.data_request())
// 		{
// 			// Read exactly 32 bytes from the ring buffer and put them
// 			// into the VS1053 buffer.
// 			//
// 			//int bytesRead = circBuffer.read((char*) VS1053_Buff, 32);

// 			//canPlayMusic = (bytesRead == 32);

// 			if (canPlayMusic)
// 			{
// 				// Actually play music, meaning: send data to VS1053
// 				//
// 				//player.playChunk(VS1053_Buff, bytesRead);

// 			} else {

// 				// Unable to read exactly 32 bytes from the ring buffer.
// 				// Send a message to fill it up and wait for enough data.
//         Serial.println("\ncanPlayMusic is FALSE\n");

// 			}	// end if (canPlayMusic)

// 		}	// end if (player.data_request())

// 	// } else {

// 	// 	// There's not enough data in the ring buffer.
// 	// 	// Send a message to fill it up and wait for enough data.
//   //   Serial.println("\nCircular buffer NOT available\n");

// 	// }	// end if (circBuffer >= 32)

// }	// end playMusicFromBuffer() -----------------------------------------------
