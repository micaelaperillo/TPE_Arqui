#ifndef TPE_ARQUI_VIDEODRIVER_H
#define TPE_ARQUI_VIDEODRIVER_H
#include <stdint.h>

void putPixel(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y);
void putPixelHex(uint32_t hexColor, uint32_t x, uint32_t y);

#endif //TPE_ARQUI_VIDEODRIVER_H
