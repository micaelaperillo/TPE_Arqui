#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>

static void int_20(uint64_t* registers), int_21(uint64_t* registers);

static void (*handlerArr[])(uint64_t* registers) = {int_20, int_21};

void irqDispatcher(uint64_t irq, uint64_t* registers) {
    handlerArr[irq](registers);
}

void int_20(uint64_t* registers) {
    timer_handler();
}

void int_21(uint64_t* registers) {
    keyboard_handler(registers);
}
