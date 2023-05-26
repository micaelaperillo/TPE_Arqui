#ifndef TPE_ARQUI_CONSOLE_H
#define TPE_ARQUI_CONSOLE_H
#include <stdint.h>

void initializeConsole();

void cPrint(const char * string);
void cPrintChar(char character);
void cNewline();
void cPrintDec(uint64_t value);
void cPrintHex(uint64_t value);
void cPrintBin(uint64_t value);
void cPrintBase(uint64_t value, uint32_t base);
void cClear();

unsigned long cGetCursor();
void cSetCursor(unsigned long pos);

#endif //TPE_ARQUI_CONSOLE_H
