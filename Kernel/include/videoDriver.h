#ifndef TPE_ARQUI_VIDEODRIVER_H
#define TPE_ARQUI_VIDEODRIVER_H
#include <stdint.h>

typedef struct Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color;

static struct Color WHITE = {255, 255, 255};
static struct Color BLACK = {0, 0, 0};
static struct Color RED = {255, 0, 0};
static struct Color GREEN = {0, 255, 0};
static struct Color BLUE = {0, 0, 255};
static struct Color YELLOW = {255, 255, 0};
static struct Color PINK = {255, 0, 255};
static struct Color CYAN = {0, 255, 255};


//DOUBLE BUFFERING OPTIONS
void enableDoubleBuffering();
void disableDoubleBuffering();
void drawBuffer();
void clearBuffer();

//PIXELS
void putPixel(Color c, uint32_t x, uint32_t y);
void putHexPixel(uint32_t hexColor, uint32_t x, uint32_t y);

//SHAPES
void putCharAt(uint32_t x, uint32_t y, char character);
void putColoredCharAt(Color c, uint32_t x, uint32_t y, char character);

void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawColoredLine(Color c, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawHexLine(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

void drawEmptyColoredCircle(Color c, uint32_t x0, uint32_t y0, uint32_t radius);
void drawEmptyHexCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);
void drawColoredCircle(Color c, uint32_t x0, uint32_t y0, uint32_t radius);
void drawHexCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);

void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawEmptyColoredRectangle(Color c, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawEmptyHexRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawColoredRectangle(Color c, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawHexRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

//UTILS
void clearScreen();
void scrollCharArea();

uint32_t getXCharSlots();
uint32_t getYCharSlots();

#endif //TPE_ARQUI_VIDEODRIVER_H
