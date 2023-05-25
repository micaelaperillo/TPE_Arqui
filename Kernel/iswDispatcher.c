#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <console.h>
#define BASE_PARAMS uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9
#define COMPLETE_PARAMS uint64_t rdi, BASE_PARAMS

typedef void (*FunctionPtr)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

void sys_write(BASE_PARAMS);//code 0
void sys_read(BASE_PARAMS);//code 1
void sys_draw(BASE_PARAMS);//code 2
void sys_buffer(BASE_PARAMS);//code 3

FunctionPtr  interruptions[] = {sys_write, sys_read, sys_draw, sys_buffer};

void swInterruptDispatcher(COMPLETE_PARAMS) {
    interruptions[rdi](rsi, rdx, rcx, r8, r9);
}

void sys_write(BASE_PARAMS) {
  char* s=(char*)rsi;
  for(int i=0;i<rdx ;i++){
    if(s[i]=='\0')
        return;
    cPrintChar(s[i]);
  }

}

void sys_read(BASE_PARAMS) {
    gets((char*)rsi);
}


//ID=2
//rsi = 0 -> pixel || 1 -> line || 2 -> empty rectangle || 3 -> rectangle || 4 -> empty circle || 5 -> filled circle
//rdx = INITIAL COORDINATES :: upper half -> x0 || lower half -> y0
//rcx = FINAL COORDINATES (used for lines :: upper half -> x1 || lower half -> y1
//r8 = DIMENSIONS (used by circles and rectangles) :: upper half -> rectangle height || lower half -> rectangle width // circle radius
//r9 = COLOR :: in hex values
void sys_draw(BASE_PARAMS) {
    uint32_t x0 = (uint32_t) (rdx >> 32);
    uint32_t y0 = (uint32_t) rdx;
    uint32_t x1 = (uint32_t) (rcx >> 32);
    uint32_t y1 = (uint32_t) rcx;

    uint32_t height = (uint32_t) (r8 >> 32);
    uint32_t width = (uint32_t) r8;

    uint32_t hexColor = (uint32_t) r9;
    switch(rsi) {
        case 0:
            putHexPixel(hexColor, x0, y0);
            break;
        case 1:
            drawHexLine(hexColor, x0, y0, x1, y1);
            break;
        case 2:
            drawEmptyHexRectangle(hexColor, x0, y0, width, height);
            break;
        case 3:
            drawHexRectangle(hexColor, x0, y0, width, height);
            break;
        case 4:
            drawEmptyHexCircle(hexColor, x0, y0, width);
            break;
        case 5:
            drawHexCircle(hexColor, x0, y0, width);
            break;
        default:
            return;
    }
}

//ID=3
//rsi = INSTRUCTION :: 0 -> disables double buffering || 1 -> enables double buffering || 2 -> swaps buffers
void sys_buffer(BASE_PARAMS) {
    switch(rsi) {
        case 0:
            disableDoubleBuffering();
            break;
        case 1:
            enableDoubleBuffering();
            break;
        case 2:
            drawBuffer();
        default:
            return;
    }
}
