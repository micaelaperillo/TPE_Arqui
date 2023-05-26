#ifndef TPE_ARQUI_STANDARDLIB_H
#define TPE_ARQUI_STANDARDLIB_H

#include <stdint.h>

void interrupt(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
void putChar(char c);
char getChar();
int compstring(const char *s1,const char *s2);
void printFormat(const char*format,...);
#endif //TPE_ARQUI_STANDARDLIB_H
