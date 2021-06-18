/*
* Implementation of playMusicQueue()
* ======================================
*
* This tasks job is to read data from the stream and place it in the queue.
*/
#include <Arduino.h>
#include <wireConfig.h>
#include <VS1053.h>
#include <populateMusicQueue.h>
#include <playMusicQueue.h>
#include <stdint.h>     // for uint8_t

#define DEBUG 1


void playMusicQueue(void *pvParam)
{
    static uint32_t prevMillis = 0;

    VS1053 player(VS1053_XCS, VS1053_XDCS, VS1053_DREQ);


    // In musicBuffer we read 4 chunks of 32 bytes from the xMusicQueue
    //
    char musicBuffer[128] __attribute__((aligned(4)));

    // In this buffer we collect data to actaully send to the VS-1053
    //
    uint8_t vs1053Buf[32]; size_t bytesRead = 32;

    for (;;)
    {
        // Read 128 bytes of stream data from the Queue and put them in the
        // musicBuffer
        //
        if (xQueueReceive(xMusicQueue, (void*)&musicBuffer, 0) == pdTRUE)
        {
            for (int i = 0; i < 4; i++)
            {
                if (sizeof(musicBuffer) >= 32)
                {
                    // Copy 32 bytes into the vs1053Buf. Copying starts at
                    // position: 0, 32, 64, 96
                    //
                    memcpy(vs1053Buf, &musicBuffer[i * 32], 32);

                    if (player.data_request())
                    {
                        // Actually send data to the VS-1053
                        //
                        // void playChunk(uint8_t *data, size_t len)
                        player.playChunk(vs1053Buf, bytesRead);
                    }

                }   // end if sizeof()

            }   // end for-loop()
           
        }   // end if xQueueReceive()

    }   // end for-loop

    #if defined(DEBUG)
       
    // Check correct stack size.
    //
    if ((millis() - prevMillis) > 6000)
    {
        uint32_t stackRemain = uxTaskGetStackHighWaterMark(NULL);
        Serial.printf("Free stack playChunk: %d\n", stackRemain);
        prevMillis = millis();
    }
    
    #endif // DEBUG

}   // end playMusicQueue()
