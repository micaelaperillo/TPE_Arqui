#ifndef TPE_ARQUI_GRAPHICS_H
#define TPE_ARQUI_GRAPHICS_H
#include <stdint.h>

void drawPixel(uint32_t hexColor, uint32_t x, uint32_t y);
void drawLine( uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

void drawEmptyCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);
void drawCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);

void drawEmptyRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

#endif //TPE_ARQUI_GRAPHICS_H
