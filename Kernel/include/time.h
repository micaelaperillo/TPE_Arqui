#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();
unsigned long ticks_elapsed();
int seconds_elapsed();
void wait(unsigned long milliseconds);

#endif
