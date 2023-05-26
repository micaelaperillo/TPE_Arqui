#include <stdint.h>
#include <console.h>

#define ZERO_EXCEPTION_ID 0
#define INVALIDO_OP_ID 6

static char* regs[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip"};

static void zero_division();
static void opinvalid(uint64_t regs, uint64_t* rip);

void printregs(uint64_t* exregs) {
	for(int i=0;i<17;i++) {
		cPrint(regs[i]);
		cPrintHex(exregs[i]);
		cPrint(" ");
	}
}

void exceptionDispatcher(int exception,uint64_t regs,uint64_t* rip) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division(regs,rip);
	}
	if (exception==INVALIDO_OP_ID)
		opinvalid(regs,rip);
}
void opinvalid(uint64_t regs,uint64_t* rip){ //todo: evitar repetir el codigo 
	cPrint("ERROR operacion invalida");
	cNewline();
	printregs(regs);
	cNewline();
	*rip=*rip+1;
}
static void zero_division(uint64_t regs,uint64_t* rip) {
	cPrint("ERROR division por 0");
	cNewline();
	printregs(regs);
	cNewline();
	*rip=*rip+1; //salta a la proxima instruccion
}

