#include <stdlib.h>
#include <connectRadio.h>
#include <populateMusicQueue.h>
#include <playMusicQueue.h>
#include <createAllTasks.h>
/*
* All xTaskCreate... goes here.
* Be very carefull about the ordening of tasks because they start running as
* soon as they're created.
*
* REMEMBER!
* =========
* Tasks are implemented as "for-ever-loops", they do NOT return anything at 
* all; they just WAIT, that is: they're SUSPENDED, or BLOCKED.
*
* Each task is like it's own self contained computer!
*/
void createAllTasks(ConnectRadio *pConnectRadio)
{
   // This is working fine: output = 1
    Serial.printf("\n1. >>>>> wClient.connected: %d\n",
                                        pConnectRadio->wClient.connected());

    xTaskCreatePinnedToCore(
        populateMusicQueue,
        "Populate Music Queue",
        1152,       // stack size in words; 1024 * 4 bytes = 4096 bytes
        (void *)pConnectRadio,
        1,          // priority
        NULL,       // taskHandle
        1           // Force core 1
    );        

    
    xTaskCreatePinnedToCore(
        playMusicQueue,
        "Play Music Queue",
        1024,
        NULL,
        1,
        NULL,
        1
    );
     
}   // end createAllTasks()
