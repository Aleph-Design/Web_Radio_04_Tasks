/*
* Put all config for all tasks in the whole project here.
* Define all macros for the project
*/
#if !defined(TASKS_CONFIG_H)
#define TASKS_CONFIG_H

#include <Arduino.h>                // Equal to: #include <FreeRTOS.h>
//#include <populateMusicQueue.h>


/*
* Declare xQueue here as EXTERN is obligatory!
* ============================================
* Written the declaration of xQueue as STATIC, means that every *.cpp file get
* its own copy, or version, of xQueue variable. Static means a global variable
* but its scope is limited to the file scope.
*/
//QueueHandle_t xMusicQueue;

#endif // TASKS_CONFIG_H
