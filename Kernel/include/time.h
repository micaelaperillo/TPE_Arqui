#ifndef TIME_H
#define TIME_H

#include <stdint.h>

// functions for RTC 

unsigned int seconds();
unsigned int minutes();
unsigned int hours();
unsigned int day();
unsigned int month();
unsigned int year();

// stores time as a string in dest
void timeToStr(char * dest);

// stores date as a string in dest
void dateToStr(char * dest);

// functions for timer tick

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void wait(uint64_t milliseconds);

#endif