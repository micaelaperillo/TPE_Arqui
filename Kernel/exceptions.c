#include <stdint.h>
#include <console.h>
#define ZERO_EXCEPTION_ID 0
static char* regs[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip"};
static void zero_division();
void printregs(uint64_t* exregs){
	for(int i=0;i<17;i++){
		cPrint(regs[i]);
		cPrintHex(exregs[i]);
		cPrint(" ");
	}
}

void exceptionDispatcher(int exception,uint64_t regs,uint64_t* rip) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division(regs,rip);
	}
}

static void zero_division(uint64_t regs,uint64_t* rip) {
	cPrint("ERROR division por 0");
	cNewline();
	printregs(regs);
	cNewline();
	*rip=*rip+1;
}

