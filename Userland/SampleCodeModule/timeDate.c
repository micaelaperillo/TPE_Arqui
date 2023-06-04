#include <stdint.h>
#include <standardLib.h>

#define SYS_GET_TIME_ID 4

enum TimeID {
    SECONDS,
    MINUTES,
    HOURS,
    DAY,
    MONTH,
    YEAR
};

unsigned int retrieve(int id) {
    unsigned int ptr;
    interrupt(SYS_GET_TIME_ID, id, (uint64_t) &ptr, 0, 0, 0);
    return ptr;
}

unsigned int getSeconds() {
    return retrieve(SECONDS);
}

unsigned int getMinutes() {
    return retrieve(MINUTES);
}

unsigned int getHours() {
    return retrieve(HOURS);
}

unsigned int getDay() {
    return retrieve(DAY);
}

unsigned int getMonth() {
    return retrieve(MONTH);
}

unsigned int getYear() {
    return retrieve(YEAR);
}


void printTime() {
    printFormat("Current time: %02d:%02d:%02d", (int)getHours(), (int)getMinutes(), (int)getSeconds());
}

void printDate() {
    printFormat("Current date: %02d/%02d/%02d", (int)getDay(), (int)getMonth(), (int)getYear());
}
