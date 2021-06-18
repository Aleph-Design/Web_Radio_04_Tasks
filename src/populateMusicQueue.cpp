/*
* Implementation of populateMusicQueue()
* ======================================
*
* This tasks job is to read data from the stream; place it in the intermediate
* buffer 'readBuffer' and send chunks of 128 bytes to the xMusicQueue.
* When that fails:
* Re-connect to the current radio station.
*/
#include <tasksConfig.h>
#include <connectRadio.h>
#include <playMusicQueue.h>
#include <populateMusicQueue.h>
#include <stdint.h>     // for uint8_t


void populateMusicQueue(void *pvParam)
{    
    // pinMode(GREEN_LED, OUTPUT);
    // pinMode(RED_LED, OUTPUT)

    bool wifiAvailable = ((ConnectRadio*)pvParam)->wClient.available();

    Serial.printf("\n>>>>> wClient available: %d\n", wifiAvailable);
 
    Serial.printf("\n\"populateMusicQueue()\" runs on core: %d\n", xPortGetCoreID());

    UBaseType_t uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    Serial.printf("\n1. HighWater: %d\n", uxHighWaterMark);

    BaseType_t qStatus;                     // Error detection

    // In readBuffer we receive the Internet stream in chunks of 128 bytes
    // aligned by 4 bytes.
    //
    char readBuffer[128] __attribute__((aligned(4)));
    uint32_t bytesInReadBuf = 0;          // bytes read from stream

    // We must have also 160000 bytes of space on the stack; so stack size 
    // must increase with 40000 words.  
    // => Question: Is the Q placed on the stack as well Or just a pointer?
    //
    uint32_t queLength = 1250;          // 160000 / 128
    uint32_t playQuart = 128;           // arbitrary number of bytes

    xMusicQueue = xQueueCreate(queLength, sizeof(playQuart));

    uint16_t xTimeInMs  = 5000;          // Wait max 5 seconds
    const TickType_t xTicksWait = pdMS_TO_TICKS(xTimeInMs);

    for (;;)
    {
        if (wifiAvailable)
        {
            // Here we read an arbitrary amount of data bytes from the stream 
            // and put them in the intermediate readBuffer.
            //
            bytesInReadBuf = ((ConnectRadio*)pvParam)->
                                    wClient.read((uint8_t *)readBuffer, 128);

            // If bytesInReadBuffer equals -1 this means nothing could be 
            // read from the stream.
            //
            if (bytesInReadBuf > 0)
            {
                // Send a chunk of 128 bytes to the play Queue
                //
                qStatus = xQueueSend(xMusicQueue, &playQuart, xTicksWait);

                if (qStatus)
                {
                    // digitalWrite(GREEN_LED, HIGH);
                    // digitalWrite(RED_LED, LOW);
                } else {
                    // digitalWrite(GREEN_LED, LOW);
                    // digitalWrite(RED_LED, HIGH);
                }  

                // UBaseType_t uxQueueMessagesWaiting( QueueHandle_t xQueue );
                // Return the number of messages stored in a queue.
                //
                // Serial.printf("\nMsg in Q: %d", uxQueueMessagesWaiting(xPlayQueue));
                // vTaskDelay(300 / portTICK_PERIOD_MS);
            }

            //Serial.printf("Read from stream\n");

        } else {
            /*
            * The stream has dried up, try to re-connect to the radio station
            * ===============================================================
            */
            Serial.printf("wClient NOT available!\n");
            
            ((ConnectRadio*)pvParam)->connectRadioStation(); 
        }

        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        // uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        // Serial.printf("2. HighWater: %d\n", uxHighWaterMark);

    }   // end for-loop()

}   // end populateMusicQueue()
