#include <stdint.h>
#include <console.h>
#include <videoDriver.h>
#include <utils.h>


void scrollUp();

static char buffer[64] = { '0' };
static uint32_t consoleCursor = 0;
static uint32_t globalCursorX = 0;
static uint32_t globalCursorY = 0;
uint32_t width = 0;
uint32_t height = 0;

void initializeConsole() {
    width = getXCharSlots();
    height = getYCharSlots();
    cPrint("[Console initialized]");
    cNewline();
}

void cPrintColored(Color c, char * string) {
    for (int i = 0; string[i] != 0; i++)
        cPrintColoredChar(c, string[i]);
}

void cPrint(char * string) {
    cPrintColored(WHITE, string);
}

void cPrintChar(char character) {
    cPrintColoredChar(WHITE, character);
}

void cPrintColoredChar(Color c, char character) {
    //writes at consoleCursor
    if (character == '\b' && consoleCursor > 0) {
        //backspace
        cErase();
        return;
    }
    if (consoleCursor >= width || character == '\n') {
        cNewline();
        return;
    }
    if (character == '\t') {
        //tab
        cPrintColoredChar(c, ' ');
        cPrintColoredChar(c, ' ');
        cPrintColoredChar(c, ' ');
        return;
    }
    putColoredCharAt(c, consoleCursor, height, character);
    consoleCursor++;
}

void gPrintColored(Color c, char* string) {
    for (int i = 0; string[i] != 0; i++)
        gPrintColoredChar(c, string[i]);
}

void gPrint(char* string) {
    gPrintColored(WHITE, string);
}

void gPrintColoredChar(Color c, char character) {
    //writes at globalCursor
    if (character == '\b' && (globalCursorX != 0 || globalCursorY != 0)) {
        //backspace
        gErase();
        return;
    }
    if (globalCursorX >= width || character == '\n') {
        if(globalCursorY >= height) {
            gNewline();
        } else {
            globalCursorX = 0;
            globalCursorY++;
        }
        return;
    }
    if (character == '\t') {
        //tab
        gPrintColoredChar(c, ' ');
        gPrintColoredChar(c, ' ');
        gPrintColoredChar(c, ' ');
        return;
    }
    putColoredCharAt(c, globalCursorX, globalCursorY, character);

    if(globalCursorX == width) {
        if(globalCursorY == height) {
            gNewline();
        } else {
            globalCursorX = 0;
            globalCursorY++;
        }
    } else {
        globalCursorX++;
    }

}

void gNewline() {
    scrollUp();
    globalCursorX = 0;
}

void gPrintDec(uint64_t value) {
    gPrintBase(value, 10);
}

void gPrintHex(uint64_t value) {
    gPrintBase(value, 16);
}

void gPrintBin(uint64_t value) {
    gPrintBase(value, 2);
}

void gPrintBase(uint64_t value, uint32_t base) {
    uintToBase(value, buffer, base);
    gPrint(buffer);
}

void gErase() {
    if(globalCursorX == 0) {
        if(globalCursorY == 0) {
            return;
        }
        globalCursorX = width - 1;
        globalCursorY--;
    } else {
        globalCursorX--;
    }
    putCharAt(globalCursorX, globalCursorY, ' ');
}

void cNewline() {
    scrollUp();
    consoleCursor = 0;
}

void cPrintDec(uint64_t value) {
    cPrintBase(value, 10);
}

void cPrintHex(uint64_t value) {
    cPrintBase(value, 16);
}

void cPrintBin(uint64_t value) {
    cPrintBase(value, 2);
}

void cPrintBase(uint64_t value, uint32_t base) {
    uintToBase(value, buffer, base);
    cPrint(buffer);
}

void cErase() {
    if(consoleCursor > 0) {
        consoleCursor--;
        putCharAt(consoleCursor, height, ' ');
    }
}

void cClear() {
    int i;

    for (i = 0; i < height * width; i++) {
        uint32_t xPos = i % width;
        uint32_t yPos = i / width;
        putCharAt(xPos, yPos, ' ');
    }
    consoleCursor = 0;
}

void scrollUp() {
    scrollCharArea();
}

void moveGlobalCursor(uint32_t x, uint32_t y) {
    globalCursorX = (x > width) ? (width) : (x);
    globalCursorY = (y > height) ? (height) : (y);
}

int getGlobalCursorX() {
    return (int)globalCursorX;
}

int getGlobalCursorY() {
    return (int)globalCursorY;
}
