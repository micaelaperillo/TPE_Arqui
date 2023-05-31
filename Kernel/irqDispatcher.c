#include <time.h>
#include <stdint.h>
#include <keyboard.h>

static void int_20(), int_21();

static void (*handlerArr[])() = {int_20, int_21};

void irqDispatcher(uint64_t irq) {
    handlerArr[irq]();
}

void int_20() {
    timer_handler();
}

void int_21() {
    keyboard_handler();
}
