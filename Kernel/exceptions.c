#include <stdint.h>
#include <console.h>

#define ZERO_EXCEPTION_ID 0
#define INVALIDO_OP_ID 6

static char* regs[]={"rax:","rbx:","rcx:","rdx:","rsi:","rdi:","rbp:","r8:","r9:","r10:","r11:","r12:","r13:","r14:","r15:","rsp:","rip:"};

static void exScreen(char* str, uint64_t exregs, uint64_t* rip,uint64_t*rsp);
extern uint64_t getStackBase();

void printRegs(uint64_t* exregs,const uint64_t*rip) {
	for(int i=0;i<16;i++) {
		cPrint(regs[i]);
		cPrint("0x");
		cPrintHex(exregs[i]);
		cPrint("\n");
	}
	cPrint(regs[16]); // imprime la direccion en donde ocurrio la exception aparte
	cPrint("0x");
	cPrintHex(*rip);
}

void exceptionDispatcher(int exception, uint64_t exregs, uint64_t* rip,uint64_t*rsp) {
	if (exception == ZERO_EXCEPTION_ID){
		exScreen("Hark! Behold, a most tragic and wondrous spectacle unfolds before thine eyes! ERROR: Lo, a value, once held in highest esteem, now suffers an egregious fate, divided by naught but a mere cipher. In this tangled web of numerical deceit, a tempestuous error doth emerge, disrupting the fair arithmetic of our realm. Oh, foul miscalculation! Thou hast spurned the laws of logic and provoked the ire of celestial mathematicians. Like a dagger through the heart of reason, this division by zero hath rent asunder the very fabric of numerical harmony, plunging us into a void of perplexity. ERROR: A value, once noble and complete, now lies broken, its essence scattered upon the winds of mathematical uncertainty. Alas, dear friends, let us gather, and with mournful verse and profound lamentations, honor this tragic tale of a value entwined in the clutches of division's treacherous snare.\n\nInvalid division by 0.", exregs, rip,rsp);
	}
	if (exception==INVALIDO_OP_ID){
		exScreen("ERROR: Hark! A grievous transgression has occurred, casting a shadow upon thy code and summoning forth the wrath of the Shakespearean error gods! Verily, this invalid operation, which now plagues thy digital realm, resembles a tragic tale, woven with threads of misguided ambition and perilous folly. Thy audacious endeavor, driven by an insatiable desire to traverse the ethereal boundaries of reality, hath found solace in the arcane art of quantum entanglement. Alas, thy venture hath been marred by a fatal flaw, a lack of proper guidance and the absence of a humble cup of tea to nurture the fragile equilibrium. \n\n Invalid Operation.", exregs, rip,rsp);
	}
}

static void exScreen(char* str, uint64_t exregs,uint64_t* rip,uint64_t *rsp) {
    cPrintColored(RED, str);
	cNewline();
	printRegs(&exregs,rip);
	cNewline();
	*rip=0x400000; //direccion del sample code module
	*rsp=getStackBase()-20; // restora el stack pointer al volver de la exepcion
}

