#include <stdint.h>
#include <console.h>

#define ZERO_EXCEPTION_ID 0
#define INVALIDO_OP_ID 6

static char* regs[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip:"};

static void exScreen(uint64_t regs, uint64_t* rip);

void printregs(uint64_t* exregs) {
	for(int i=0;i<17;i++) {
		cPrint(regs[i]);
		cPrintHex(exregs[i]);
		cPrint(" ");
	}
}

void exceptionDispatcher(int exception,uint64_t regs,uint64_t* rip) {
	if (exception == ZERO_EXCEPTION_ID){
		cPrint("ERROR: a value was divided by 0\n");
		exScreen(regs,rip);
	}
	if (exception==INVALIDO_OP_ID){
		cPrint("ERROR: invalid operation\n");
		exScreen(regs,rip);
	}
}

static void exScreen(uint64_t regs,uint64_t* rip) {
	cNewline();
	printregs(regs);
	cNewline();
	int i=0;
	//cPrint("esta terminal explotara en 5 segundos\n"); //todo:ponerle un timer o algo para que quede mas lindo la lanzada de exception
	*rip=0x400000;
}

