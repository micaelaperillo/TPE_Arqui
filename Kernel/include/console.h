#ifndef TPE_ARQUI_CONSOLE_H
#define TPE_ARQUI_CONSOLE_H
#include <stdint.h>
#include <videoDriver.h>

void initializeConsole();

//#######################################################
//WRITES AT GLOBAL CURSOR

// prints the string in the color c
void gPrintColored(Color c, char * string);

// prints string in the default color, which is WHITE
void gPrint(char * string);

// prints char character in the color c
void gPrintColoredChar(Color c, char character);

// prints new line
void gNewline();

// prints value, which is a decimal
void gPrintDec(uint64_t value);

// prints value, which is a hexadecimal
void gPrintHex(uint64_t value);

// prints value, which is a binary
void gPrintBin(uint64_t value);

// prints value, according to its base
void gPrintBase(uint64_t value, uint32_t base);

void gErase();

void moveGlobalCursor(uint32_t x, uint32_t y);

int getGlobalCursorX();

int getGlobalCursorY();

//#######################################################
//WRITES AT CONSOLE CURSOR


// prints the string in the color c
void cPrintColored(Color c, char * string);

// prints string in the default color, which is WHITE
void cPrint(char * string);

// prints char character in the color c
void cPrintColoredChar(Color c, char character);

// prints character in the default color, which is WHITE
void cPrintChar(char character);

// prints new line
void cNewline();

// prints value, which is a decimal
void cPrintDec(uint64_t value);

// prints value, which is a hexadecimal
void cPrintHex(uint64_t value);

// prints value, which is a binary
void cPrintBin(uint64_t value);

// prints value, according to its base
void cPrintBase(uint64_t value, uint32_t base);

void cErase();

void cClear();

#endif //TPE_ARQUI_CONSOLE_H
