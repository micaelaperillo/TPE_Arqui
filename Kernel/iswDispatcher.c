#include <stdint.h>
#include <console.h>

#define BASE_PARAMS uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9
#define COMPLETE_PARAMS uint64_t rdi, BASE_PARAMS

typedef void (*FunctionPtr)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

void sys_write(BASE_PARAMS);

FunctionPtr  interruptions[] = {sys_write};

void swInterruptDispatcher(COMPLETE_PARAMS) {
    interruptions[rdi](rsi, rdx, rcx, r8, r9);
}

void sys_write(BASE_PARAMS) {
    //TODO mejorarla
    cPrint((char*)rsi);
}