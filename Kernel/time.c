#include <time.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void wait(float seconds) {
    float aux1, aux2;
    aux1 = aux2 =(float) seconds_elapsed();
    while(1) {
        if((aux1 > aux2 && (aux1 - aux2) > seconds) || (aux2 > aux1 && (aux2 - aux1) > seconds)) {
            return;
        }
        aux2 = seconds_elapsed();
    }
}
