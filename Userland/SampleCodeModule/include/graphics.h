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

/**
 * Draws a pixel in the front or back buffer depending on whether double buffering was activated or not
 * @param hexColor Color value in hexadecimal
 * @param x X coordinate of the pixel, dimensions are specified in graphics.c
 * @param y Y coordinate of the pixel
 */
void drawPixel(uint32_t hexColor, uint32_t x, uint32_t y);

/**
 * Draws a line in the front or back buffer from two coordinates
 * @param hexColor Color value in hexadecimal
 * @param x0 Initial x coordinate
 * @param y0 Initial y coordinate
 * @param x1 Final x coordinate
 * @param y1 Final y coordinate
 */
void drawLine( uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

//#########################
/**
 * Draws an empty circle in the front or back double buffer
 * @param hexColor Color in hexadecimal
 * @param x0 X coordinate representing the center of the circle
 * @param y0 Y coordinate representing the center of the circle
 * @param radius Circle radius
 */
void drawEmptyCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);

/**
 * Draws a circle in the front or back buffer, see function above for the parameters' descriptions
 * @param hexColor
 * @param x0
 * @param y0
 * @param radius
 */
void drawCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius);

//#########################
/**
 * Draws an empty rectangle in the front or back buffer
 * @param hexColor Color in hexadecimal value
 * @param x X coordinate for top-left corner
 * @param y Y coordinate for top-left corner
 * @param width Rectangle's width
 * @param height Rectangle's height
 */
void drawEmptyRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

/**
 * Draws a rectangle in the front or back buffer, see function above for the parameters' description
 * @param hexColor
 * @param x
 * @param y
 * @param width
 * @param height
 */
void drawRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

//#########################
/**
 * Draws a number in the front or back buffer
 * @param x X coordinate for top-left corner
 * @param y Y coordinate for top-left corner
 * @param height Number's height
 * @param hexColor Color in hexadecimal
 * @param width Space used by the number
 * @param line_width Number's lines width
 * @param number Number from 0-9
 */
void drawNumber(uint32_t x, uint32_t y, uint32_t height, uint32_t hexColor, uint32_t width, uint32_t line_width, uint32_t number);

//#########################
/**
 * Sets all pixels in the front or back buffer to black
 */
void clearScreen();


//#########################
/**
 * Enables double buffering, if enabled, all functions will draw to the back buffer
 */
void enableDoubleBuffering();

/**
 * Disables double buffering, if disabled, all functions will draw to the front buffer
 */
void disableDoubleBuffering();

/**
 * Swaps the front and back buffer, clears the screen if double buffering is disabled
 */
void swapBuffer();


#endif //TPE_ARQUI_GRAPHICS_H
