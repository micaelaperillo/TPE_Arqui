#ifndef TPE_ARQUI_GRAPHICS_H
#define TPE_ARQUI_GRAPHICS_H
#include <stdint.h>

static const uint32_t WHITE = 0xFFFFFF;
static const uint32_t BLACK = 0x000000;
static const uint32_t RED = 0xFF0000;
static const uint32_t GREEN = 0x00FF00;
static const uint32_t BLUE = 0x0000FF;
static const uint32_t YELLOW = 0xFFFF00;
static const uint32_t PINK = 0xFF00FF;
static const uint32_t CYAN = 0x00FFFF;


void drawPixel(uint32_t hexColor, uint32_t x, uint32_t y);
void drawLine( uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

void drawEmptyCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);
void drawCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);

void drawEmptyRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void clearScreen();

void enableDoubleBuffering();
void disableDoubleBuffering();
void swapBuffer();
void drawNumber(uint32_t x, uint32_t y, uint32_t height, uint32_t hexColor, uint32_t width, uint32_t line_width, uint32_t number);

#endif //TPE_ARQUI_GRAPHICS_H
