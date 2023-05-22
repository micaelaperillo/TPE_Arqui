#ifndef TPE_ARQUI_VIDEODRIVER_H
#define TPE_ARQUI_VIDEODRIVER_H
#include <stdint.h>

typedef struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color;

static const Color WHITE = {255, 255, 255};
static const Color BLACK = {0, 0, 0};

void putPixel(Color c, uint32_t x, uint32_t y);
void putPixelHex(uint32_t hexColor, uint32_t x, uint32_t y);
void putCharAt(uint32_t x, uint32_t y, char character);
void putColoredCharAt(Color c, uint32_t x, uint32_t y, char character);
void drawLine(uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf);
void drawColoredLine(Color c, uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf);
void drawEmptyColoredCircle(Color c, uint32_t xi, uint32_t yi, uint32_t radius);
void drawColoredCircle(Color c, uint32_t xi, uint32_t yi, uint32_t radius);
void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawColoredRectangle(Color c, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

uint32_t getXCharSlots();
uint32_t getYCharSlots();

#endif //TPE_ARQUI_VIDEODRIVER_H
