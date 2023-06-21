#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

// handles when a key is pressed
void keyboard_handler(uint64_t *registers);

// returns if a key (any) is pressed
uint8_t keyPressed();

// gets char, from the keyboard
void gets(char * s);

// gets string, from the keyboard
char getc();

#endif
