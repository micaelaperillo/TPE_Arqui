#include <stdint.h>
#include <standardLib.h>

#define SYS_GET_REGS_ID 4

static int regsAmount = 17;
static char * regsStr[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip:"};

extern uint64_t* current_regs();

void printRegisters() {
    //prints the registers at this exact moment, values will be lost between the prompt and here
    uint64_t * regs = current_regs();
    printFormat("System registers:");
    for(int i=0; i<regsAmount; i++) {
        printFormat("\n\t%s%x", regsStr[i], regs[i]);
    }
}