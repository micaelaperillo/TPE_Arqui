#include <bitmapFont.h>
#include <stdint.h>
#include <videoDriver.h>

//################################################
//Este pedazo de codigo fue dado por la cátedra de Arquitectura de Computadoras

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

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8
#define SIZE_MULT 1
#define X_PADDING 0      //empty pixels next to each char
#define Y_PADDING 0
#define X_BORDER_PADDING 1
#define Y_BORDER_PADDING 1

#define XDIM ((VBE_mode_info->width) / ((CHAR_WIDTH + X_PADDING) * SIZE_MULT))
#define YDIM ((VBE_mode_info->height) / ((CHAR_HEIGHT + Y_PADDING) * SIZE_MULT))

void putPixel(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y) {
    if(x >= VBE_mode_info->width || x < 0 || y >= VBE_mode_info->height || y < 0) {
        return;
    }
    uint8_t * videoPtr = VBE_mode_info->framebuffer;
    int offset = y * VBE_mode_info->pitch + x * (VBE_mode_info->bpp / 8);
    videoPtr[offset] = b;
    videoPtr[offset+1] = g;
    videoPtr[offset+2] = r;
}

//################################################

void putPixelHex(uint32_t hexColor, uint32_t x, uint32_t y) {
    uint8_t r, g, b;
    b = hexColor & 255;
    g = (hexColor >> 8) & 255;
    r = (hexColor >> 16) & 255;
    putPixel(r, g, b, x, y);
}

//using Bresenham's line drawing algorithm, taken from https://www.javatpoint.com/computer-graphics-bresenhams-line-algorithm and modified
void drawColoredLine(uint8_t r, uint8_t g, uint8_t b, uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf) {
    int dx, dy, p, x, y;
    if(xf < xi) {
        int aux = xi;
        xi = xf;
        xf = aux;
    }
    dx=xf-xi;
    dy=yf-yi;
    x=xi;
    y=yi;
    p=2*dy-dx;
    while(x<xf)
    {
        if(p>=0)
        {
            putPixel(r, g, b, x, y);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            putPixel(r, g, b, x, y);
            p=p+2*dy;}
        x=x+1;
    }
}

void drawLine(uint32_t xi, uint32_t yi, uint32_t xf, uint32_t yf) {
    drawColoredLine(255, 255, 255, xi, yi, xf, yf);
}

void _eightWaySymmetryLine(uint8_t r, uint8_t g, uint8_t b, uint32_t xc, uint32_t yc, uint32_t x, uint32_t y) {
    putPixel(r, g, b, x+xc, y+yc);
    putPixel(r, g, b, x+xc, -y+yc);
    putPixel(r, g, b, -x+xc, -y+yc);
    putPixel(r, g, b, -x+xc, y+yc);
    putPixel(r, g, b, y+xc, x+yc);
    putPixel(r, g, b, y+xc, -x+yc);
    putPixel(r, g, b, -y+xc, x+yc);
    putPixel(r, g, b, -y+xc, -x+yc);
}

void drawEmptyColoredCircle(uint8_t r, uint8_t g, uint8_t b, uint32_t xi, uint32_t yi, uint32_t radius) {
    //using Bresenham's circle drawing algorithm, taken from https://www.javatpoint.com/computer-graphics-bresenhams-circle-algorithm and modified
    int x=0,y=radius,d=3-(2*radius);
    _eightWaySymmetryLine(r, g, b, xi, yi, x, y);

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
        _eightWaySymmetryLine(r, g, b, xi, yi, x, y);
    }
}


void drawColoredRectangle(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            putPixel(r, g, b, x+j, y+i);
        }
    }
}

void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    drawColoredRectangle(255, 255, 255, x, y, width, height);
}

//code taken from https://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers and modified
void _drawChar(uint32_t r, uint32_t g, uint32_t b, uint32_t xPixel, uint32_t yPixel, char c) {
    uint8_t i, j;

    // Convert the character to an index
    c = c & 0x7F;
    const uint8_t *chr = font[c];

    // Draw pixels
    for (j = 0; j < CHAR_HEIGHT; j++) {
        for (i = 0; i < CHAR_WIDTH; i++) {
            if(chr[j] & (1<<i)) {
                drawColoredRectangle(r, g, b, (xPixel + i) * SIZE_MULT, (yPixel + j) * SIZE_MULT, SIZE_MULT, SIZE_MULT);
            }
            else {
                drawColoredRectangle(0, 0, 0, (xPixel + i) * SIZE_MULT, (yPixel + j) * SIZE_MULT, SIZE_MULT, SIZE_MULT);    //turns the pixel off
            }
        }
    }
}

void putColoredCharAt(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y, char c) {
    if (x > XDIM || y > YDIM || x < 0 || y < 0) {
        return;
    }
    uint32_t xCoord = (x * (CHAR_WIDTH + X_PADDING)) + X_BORDER_PADDING;
    uint32_t yCoord = (y * (CHAR_HEIGHT + Y_PADDING)) + Y_BORDER_PADDING;
    _drawChar(r, g, b, xCoord, yCoord, c);
}

void putCharAt(uint32_t x, uint32_t y, char c) {
    putColoredCharAt(255, 255, 255, x, y, c);
}

uint32_t getXCharSlots() {
    return XDIM;
}

uint32_t getYCharSlots() {
    return YDIM;
}