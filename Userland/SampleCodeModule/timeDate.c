#include <stdint.h>
#include <standardLib.h>

#define SYS_GET_TIME_ID 6

enum TimeID {
    SECONDS,
    MINUTES,
    HOURS,
    DAY,
    MONTH,
    YEAR
};

unsigned int retrieve(int id) {
    unsigned int* ptr = 0;
    interrupt(SYS_GET_TIME_ID, id, ptr, 0, 0, 0);
    return *ptr;
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

//TODO modificarlo una vez que este terminado printf
void printTime() {
    printFormat("%d:%d:%d", (int)getHours(), (int)getMinutes(), (int)getSeconds());
}

void printDate() {
    printFormat("%d/%d/%d", (int)getDay(), (int)getMonth(), (int)getYear());
}