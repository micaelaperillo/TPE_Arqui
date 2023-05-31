#include <sound.h>
#include <time.h>
#include <stdint.h>

extern void play_sound(unsigned int frequency);
extern void stop_sound();
extern timer_wait(unsigned int time);

void play_beep(uint32_t freq, uint32_t time) {
    uint32_t div = 1193180/freq;

    play_sound(div);
    wait(time);
    stop_sound();
}