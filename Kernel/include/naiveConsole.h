#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

// prints string
void ncPrint(const char * string);

// prints char
void ncPrintChar(char character);

// prints new line
void ncNewline();

// prints value, which is a decimal
void ncPrintDec(uint64_t value);

// prints value, which is a hexadecimal
void ncPrintHex(uint64_t value);

// prints value, which is a binary
void ncPrintBin(uint64_t value);

// prints value in the base indicated
void ncPrintBase(uint64_t value, uint32_t base);

// clears screen
void ncClear();

#endif