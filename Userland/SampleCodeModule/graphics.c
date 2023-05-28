#include <standardLib.h>
#include <stdint.h>

#define SCREEN_HEIGHT 1024
#define SCREEN_WIDTH 768

#define SYS_DRAW_ID 2
#define SYS_BUFFER_ID 3

enum SHAPE_ID {
    PIXEL,
    LINE,
    EMPTY_RCT,
    RCT,
    EMPTY_CIRCLE,
    CIRCLE,
    CLR
};

enum BUFFER_ID {
    DISABLE_BUFF,
    ENABLE_BUFF,
    SWAP_BUFF
};

uint64_t join(uint32_t upper, uint32_t lower) {
    return ((uint64_t) upper << 32) | lower;
}

//draw a pixel at the specified coordinate
void drawPixel(uint32_t hexColor, uint32_t x, uint32_t y) {
    uint64_t coords = join(x, y);
    interrupt(SYS_DRAW_ID, PIXEL, coords, 0, 0, hexColor);
}

//draws a line connecting (x0,y0) and (x1,y1)
void drawLine( uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    uint64_t coords0 = join(x0, y0);
    uint64_t coords1 = join(x1, y1);
    interrupt(SYS_DRAW_ID, LINE, coords0, coords1, 0, hexColor);
}


//draws a circle, uses the coordinates as its middle point
void drawEmptyCircle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t radius) {
    uint64_t coords = join(x, y);
    interrupt(SYS_DRAW_ID, EMPTY_CIRCLE, coords, 0, radius, hexColor);
}

// "
void drawCircle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t radius) {
    uint64_t coords = join(x, y);
    interrupt(SYS_DRAW_ID, CIRCLE, coords, 0, radius, hexColor);
}

//draws a rectangle, the coordinates given represent the upper-left position of the rectangle
void drawEmptyRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    uint64_t coords = join(x, y);
    uint64_t dim = join(height, width);
    interrupt(SYS_DRAW_ID, EMPTY_RCT, coords, 0, dim, hexColor);
}

//"
void drawRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    uint64_t coords = join(x, y);
    uint64_t dim = join(height, width);
    interrupt(SYS_DRAW_ID, RCT, coords, 0, dim, hexColor);
}

void clearScreen() {
    interrupt(SYS_DRAW_ID, CLR, 0, 0, 0, 0);
}

void enableDoubleBuffering() {
    interrupt(SYS_BUFFER_ID, ENABLE_BUFF, 0, 0, 0, 0);
}

void disableDoubleBuffering() {
    interrupt(SYS_BUFFER_ID, DISABLE_BUFF, 0, 0, 0, 0);
}

void swapBuffer() {
    interrupt(SYS_BUFFER_ID, SWAP_BUFF, 0, 0, 0, 0);
}
