#ifndef TPE_ARQUI_VIDEODRIVER_H
#define TPE_ARQUI_VIDEODRIVER_H
#include <stdint.h>

void putPixel(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y);
void putPixelHex(uint32_t hexColor, uint32_t x, uint32_t y);
void putCharAt(uint32_t x, uint32_t y, char c);
void putColoredCharAt(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y, char c);
void drawLine(uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf);
void drawColoredLine(uint8_t r, uint8_t g, uint8_t b, uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf);
void drawEmptyColoredCircle(uint8_t r, uint8_t g, uint8_t b, uint32_t xi, uint32_t yi, uint32_t radius);
void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawColoredRectangle(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

uint32_t getXCharSlots();
uint32_t getYCharSlots();

#endif //TPE_ARQUI_VIDEODRIVER_H
