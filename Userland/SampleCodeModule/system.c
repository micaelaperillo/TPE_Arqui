#include <stdint.h>
#include <timeDate.h>
#include <standardLib.h>

#define SYS_DETECT_KEY_PRESS_ID 5
#define SYS_WAIT_ID 6

static int regsAmount = 17;
static char * regsStr[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:",
                         "r15:","rsp:","rip:"};

extern uint64_t* current_regs();

void printRegisters() {
    //prints the registers at this exact moment, values will be lost between the prompt and here
    uint64_t * regs = current_regs();
    printFormat("System registers:");
    for(int i=0; i<regsAmount; i++) {
        printFormat("\n\t-%s%x ", regsStr[i], regs[i]);
    }
}

uint8_t keyPress() {
    uint8_t b;
    interrupt(SYS_DETECT_KEY_PRESS_ID, (uint64_t)&b, 0, 0, 0, 0);
    return b;
}

void wait(unsigned long milliseconds) {
    interrupt(SYS_WAIT_ID, milliseconds, 0, 0, 0, 0);
}
