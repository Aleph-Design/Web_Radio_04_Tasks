#if !defined(PLAY_MUSIC_QUEUE_H)
#define PLAY_MUSIC_QUEUE_H

extern QueueHandle_t xMusicQueue;

void playMusicQueue(void *pvParam);

#endif // PLAY_MUSIC_QUEUE_H
