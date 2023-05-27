#ifndef TIME_H
#define TIME_H

// functions for RTC

unsigned int seconds();
unsigned int minutes();
unsigned int hours();
unsigned int day();
unsigned int month();
unsigned int year();
void timeToStr(char * dest);
void dateToStr(char * dest);

// functions for timer tick

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void wait(unsigned long milliseconds);

#endif