#include <stdint.h>
#include <console.h>

#define ZERO_EXCEPTION_ID 0
#define INVALIDO_OP_ID 6

static char* regs[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip:"};

static void exScreen(char* str, uint64_t exregs, uint64_t* rip);

void printRegs(uint64_t* exregs) {
	for(int i=0;i<17;i++) {
		cPrint(regs[i]);
		cPrintHex(exregs[i]);
		cPrint(" ");
	}
}

void exceptionDispatcher(int exception, uint64_t exregs, uint64_t* rip) {
	if (exception == ZERO_EXCEPTION_ID){
		exScreen("Hark! Behold, a most tragic and wondrous spectacle unfolds before thine eyes! ERROR: Lo, a value, once held in highest esteem, now suffers an egregious fate, divided by naught but a mere cipher. In this tangled web of numerical deceit, a tempestuous error doth emerge, disrupting the fair arithmetic of our realm. Oh, foul miscalculation! Thou hast spurned the laws of logic and provoked the ire of celestial mathematicians. Like a dagger through the heart of reason, this division by zero hath rent asunder the very fabric of numerical harmony, plunging us into a void of perplexity. ERROR: A value, once noble and complete, now lies broken, its essence scattered upon the winds of mathematical uncertainty. Alas, dear friends, let us gather, and with mournful verse and profound lamentations, honor this tragic tale of a value entwined in the clutches of division's treacherous snare.", exregs, rip);
	}
	if (exception==INVALIDO_OP_ID){
		exScreen("ERROR: invalid operation", exregs, rip);
	}
}

static void exScreen(char* str, uint64_t exregs,uint64_t* rip) {
    cPrintColored(RED, str);
	cNewline();
	printRegs(exregs);
	cNewline();
	int i=0;
	//cPrint("esta terminal explotara en 5 segundos\n"); //todo:ponerle un timer o algo para que quede mas lindo la lanzada de exception
	*rip=0x400000;
}

