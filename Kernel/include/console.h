#ifndef TPE_ARQUI_CONSOLE_H
#define TPE_ARQUI_CONSOLE_H
#include <stdint.h>
#include <videoDriver.h>

void initializeConsole();

void cPrintColored(Color c, char * string);
void cPrint(char * string);
void cPrintColoredChar(Color c, char character);
void cPrintChar(char character);
void cNewline();
void cPrintDec(uint64_t value);
void cPrintHex(uint64_t value);
void cPrintBin(uint64_t value);
void cPrintBase(uint64_t value, uint32_t base);
void cErase();
void cClear();


#endif //TPE_ARQUI_CONSOLE_H
