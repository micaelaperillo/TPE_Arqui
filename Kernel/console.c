#include <stdint.h>
#include <console.h>
#include <videoDriver.h>
#include <utils.h>

void scrollUp();

static char buffer[64] = { '0' };
static uint32_t consoleCursor = 0;
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
    if (character == '\b' && consoleCursor > 0) {
        //backspace
        putColoredCharAt(c, --consoleCursor, height, character);
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
