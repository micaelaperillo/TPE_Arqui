#include <stdint.h>
#include <standardLib.h>

#define SYS_DETECT_KEY_PRESS_ID 5
#define SYS_WAIT_ID 6
#define SYS_SOUND_ID 7



extern uint64_t* current_regs();

uint8_t keyPress() {
    uint8_t b;
    interrupt(SYS_DETECT_KEY_PRESS_ID, (uint64_t)&b, 0, 0, 0, 0);
    return b;
}

void wait(uint64_t milliseconds) {
    interrupt(SYS_WAIT_ID, milliseconds, 0, 0, 0, 0);
}

void play_beep(uint32_t frequency, uint32_t duration) {
    interrupt(SYS_SOUND_ID, frequency, duration,  0, 0, 0);
}
