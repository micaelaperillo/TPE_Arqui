#include <time.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

unsigned long ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void wait(unsigned long milliseconds) {
    unsigned int initTicks = ticks;
    while ((ticks - initTicks) < (milliseconds / 55)) {

    }
}
