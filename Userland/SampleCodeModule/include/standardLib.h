#ifndef TPE_ARQUI_STANDARDLIB_H
#define TPE_ARQUI_STANDARDLIB_H

#include <stdint.h>

#define null ((void*)0)

/**
 * Calls a system interruption
 * @param rdi
 * @param rsi
 * @param rdx
 * @param rcx
 * @param r8
 * @param r9
 */
void interrupt(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

/**
 * Writes a character in the console
 * @param c
 */
void putChar(char c);

/**
 * Retrieves a key press from the keyboard, waits until input is recieved before continuing
 * @return Pressed character
 */
char getChar();

/**
 * Prints a string to screen, can print parameters passed
 * @param format %d for decimal | %x for hexadecimal | %s for string
 * @param ... Values representing the value requested in order of appearance
 */
void printFormat(const char*format,...);

/**
 * Compares two strings
 * @param s1
 * @param s2
 * @return 0 if the strings are equal
 */
int compString(const char *s1,const char *s2);

uint8_t isCharPressed(char c);
#endif //TPE_ARQUI_STANDARDLIB_H
