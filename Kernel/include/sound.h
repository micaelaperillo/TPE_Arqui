#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

// plays a 'beep' sound, for the specified frequency and duration
void play_beep(uint32_t freq, uint32_t time);

#endif