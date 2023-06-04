#include <bitmapFont.h>
#include <stdint.h>
#include <videoDriver.h>
#include <lib.h>

// codigo dado por la cátedra de Arquitectura de Computadoras

struct vbe_mode_info_structure {
    uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;			// deprecated
    uint8_t window_b;			// deprecated
    uint16_t granularity;		// deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;			// number of bytes per horizontal line
    uint16_t width;			// width in pixels
    uint16_t height;			// height in pixels
    uint8_t w_char;			// unused...
    uint8_t y_char;			// ...
    uint8_t planes;
    uint8_t bpp;			// bits per pixel in this mode
    uint8_t banks;			// deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

//################################################

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BYTES_PER_PIXEL 3
#define BUFFER_SIZE SCREEN_HEIGHT * SCREEN_WIDTH * BYTES_PER_PIXEL

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8
#define SIZE_MULT 1

#define WIDTH_PADDING 2
#define HEIGHT_PADDING 6

#define XDIM 96
#define YDIM 48

#define X_MARGIN 32
#define Y_MARGIN 48

#define TRUE 1
#define FALSE 0

int doubleBufferingEnabled = FALSE;
static uint8_t videoBuffer[BUFFER_SIZE] = {0};

void hexToColor(uint32_t hexColor, Color* c);

void enableDoubleBuffering() {
    doubleBufferingEnabled = TRUE;
}

void disableDoubleBuffering() {
    doubleBufferingEnabled = FALSE;
}

void drawBuffer() {
    memcut(VBE_mode_info->framebuffer, videoBuffer,
           VBE_mode_info->width * (VBE_mode_info->bpp / 8) * VBE_mode_info->height);
}

void clearBuffer() {
    memset(videoBuffer, 0, BUFFER_SIZE);
}

void scrollCharArea() {
    //currently only scrolls up the area reserved by the chars, excluding the margins
    uint32_t vPixels = CHAR_HEIGHT + HEIGHT_PADDING;
    uint64_t xLen = (XDIM * (CHAR_WIDTH + WIDTH_PADDING)) * (VBE_mode_info->bpp / 8);
    //goes to the first pixel in the char area
    uint64_t currMem = VBE_mode_info->framebuffer + (VBE_mode_info->bpp/8) * (X_MARGIN + VBE_mode_info->width * Y_MARGIN);
    uint64_t offset = VBE_mode_info->width * vPixels * (VBE_mode_info->bpp / 8);
    for(int i=0; i<YDIM + 1; i++) {
        for(int j=0; j<vPixels; j++) {
            memcpy(currMem, currMem + offset, xLen);
            currMem += VBE_mode_info->width * (VBE_mode_info->bpp / 8);//jumps to the pixels below
        }
        //once it finishes it has copied an entire block of characters
    }
}

void putPixel(Color c, uint32_t x, uint32_t y) {
    if(x >= VBE_mode_info->width || x < 0 || y >= VBE_mode_info->height || y < 0) {
        return;
    }
    if(doubleBufferingEnabled) {
        //changes the pixel in the buffer and finishes, no need to change anything else
        int offset = y * VBE_mode_info->pitch + x * (VBE_mode_info->bpp / 8);
        videoBuffer[offset] = c.b;
        videoBuffer[offset+1] = c.g;
        videoBuffer[offset+2] = c.r;
        return;
    }
    //double buffering is disabled, it paints directly to the screen
    uint8_t * videoPtr = VBE_mode_info->framebuffer;
    int offset = y * VBE_mode_info->pitch + x * (VBE_mode_info->bpp / 8);
    videoPtr[offset] = c.b;
    videoPtr[offset+1] = c.g;
    videoPtr[offset+2] = c.r;
}

void putHexPixel(uint32_t hexColor, uint32_t x, uint32_t y) {
    Color c;
    hexToColor(hexColor, &c);
    putPixel(c, x, y);
}

void drawColoredLine(Color c, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    //code written by bert, taken from https://gist.github.com/bert/1085538 and modified
    int aux1 = (x1 > x0)?(x1-x0):(x0 - x1), aux2 = (y1 > y0)?(y0-y1):(y1 - y0);
    int dx =  aux1, sx = x0 < x1 ? 1 : -1;
    int dy = aux2, sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for (;;){  /* loop */
        putPixel(c, x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void drawHexLine(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    Color c;
    hexToColor(hexColor, &c);
    drawColoredLine(c, x0, y0, x1, y1);
}

void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    drawColoredLine(WHITE, x0, y0, x1, y1);
}

void _eightWaySymmetryLine(Color c, uint32_t xc, uint32_t yc, uint32_t x, uint32_t y) {
    putPixel(c, x+xc, y+yc);
    putPixel(c, x+xc, -y+yc);
    putPixel(c, -x+xc, -y+yc);
    putPixel(c, -x+xc, y+yc);
    putPixel(c, y+xc, x+yc);
    putPixel(c, y+xc, -x+yc);
    putPixel(c, -y+xc, x+yc);
    putPixel(c, -y+xc, -x+yc);
}

void drawEmptyColoredCircle(Color c, uint32_t x0, uint32_t y0, uint32_t radius) {
    //using Bresenham's circle drawing algorithm, taken from https://www.javatpoint.com/computer-graphics-bresenhams-circle-algorithm and modified
    int x=0,y=radius,d=3-(2*radius);
    _eightWaySymmetryLine(c, x0, y0, x, y);

    while(x<=y)
    {
        if(d<=0)
        {
            d=d+(4*x)+6;
        }
        else
        {
            d=d+(4*x)-(4*y)+10;
            y=y-1;
        }
        x=x+1;
        _eightWaySymmetryLine(c, x0, y0, x, y);
    }
}

void drawEmptyHexCircle(uint32_t hexColor, uint32_t x0, uint32_t y0, uint32_t radius) {
    Color c;
    hexToColor(hexColor, &c);
    drawEmptyColoredCircle(c, x0, y0, radius);
}

void drawColoredCircle(Color c, uint32_t x1, uint32_t y1, uint32_t radius) {
    //function written by palm3D, taken from https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
    //currently being used because it doesn't need the sqrt() function
    int r = (int)radius;
    for(int y=-r; y<=r; y++)
        for(int x=-r; x<=r; x++)
            if(x*x+y*y <= r*r)
                putPixel(c, x1+x, y1+y);
}

void drawHexCircle(uint32_t hexColor, uint32_t x1, uint32_t y1, uint32_t radius) {
    Color c;
    hexToColor(hexColor, &c);
    drawColoredCircle(c, x1, y1, radius);
}

void drawColoredRectangle(Color c, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            putPixel(c, x+j, y+i);
        }
    }
}

void drawHexRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    Color c;
    hexToColor(hexColor, &c);
    drawColoredRectangle(c, x, y, width, height);
}

void drawEmptyColoredRectangle(Color c, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    int drawing = 1;
    for(int i=0, j=0;drawing; i++, j++) {
        drawing = 0;
        if(i<width) {
            putPixel(c, x + i, y);
            putPixel(c, x + i, y + height);
            drawing = 1;
        }
        if(j<height) {
            putPixel(c, x, y + j);
            putPixel(c, x + width, y + j);
            drawing = 1;
        }
    }
}

void drawEmptyHexRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    Color c;
    hexToColor(hexColor, &c);
    drawEmptyColoredRectangle(c, x, y, width, height);
}

void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    drawColoredRectangle(WHITE, x, y, width, height);
}

void _drawChar(Color c, uint32_t xPixel, uint32_t yPixel, unsigned char character) {
    uint8_t i, j;

    //converts the character to an index
    character = character & 0x7F;
    const char *chr = font[character];

    //draws the pixels
    for (j = 0; j < CHAR_HEIGHT; j++) {
        for (i = 0; i < CHAR_WIDTH; i++) {
            if(chr[j] & (1<<i)) {
                //it draws rectangles in case size_mult > 1, which is currently not supported
                //this was left as it is easier to adapt it in case it is supported again
                drawColoredRectangle(c, (xPixel + i) * SIZE_MULT, (yPixel + j) * SIZE_MULT, SIZE_MULT, SIZE_MULT);
            }
            else {
                drawColoredRectangle(BLACK, (xPixel + i) * SIZE_MULT, (yPixel + j) * SIZE_MULT, SIZE_MULT, SIZE_MULT);
                //turns the pixel "off"
            }
        }
    }
}

void putColoredCharAt(Color c, uint32_t x, uint32_t y, char character) {
    if (x > XDIM || y > YDIM || x < 0 || y < 0) {
        return;
    }
    uint32_t xCoord = (x * (CHAR_WIDTH + WIDTH_PADDING)) + X_MARGIN;
    uint32_t yCoord = (y * (CHAR_HEIGHT + HEIGHT_PADDING)) + Y_MARGIN;
    _drawChar(c, xCoord, yCoord, character);
}

void putCharAt(uint32_t x, uint32_t y, char character) {
    putColoredCharAt(WHITE, x, y, character);
}

void clearScreen() {
    uint8_t * videoPtr = VBE_mode_info->framebuffer;
    memset(videoPtr, 0, VBE_mode_info->width * VBE_mode_info->height * (VBE_mode_info->bpp / 8));
}

void hexToColor(uint32_t hexColor, Color* c) {
    c->b = hexColor & 255;
    c->g = (hexColor >> 8) & 255;
    c->r = (hexColor >> 16) & 255;
}

uint32_t getXCharSlots() {
    return XDIM;
}

uint32_t getYCharSlots() {
    return YDIM;
}
