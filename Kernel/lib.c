#include <stdint.h>
#include <console.h>

static char* regs[]={"r15: ", "r14: ", "r13: ", "r12: ", "r11: ", "r10: ", "r9: ","r8: ", "rsi: ", "rdi: ", "rbp: ", "rdx: ", "rcx: ", "rbx: ","rax: ", "rip: ", "rsp: "};

static void exScreen(char* str, uint64_t* stack);

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void * memcut(void * destination, void * source, uint64_t length)
{
    /*
    * like memcpy, but sets the source to 0
    */
    uint64_t i;

    if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
        (uint64_t)source % sizeof(uint32_t) == 0 &&
        length % sizeof(uint32_t) == 0)
    {
        uint32_t *d = (uint32_t *) destination;
        uint32_t *s = (uint32_t *)source;

        for (i = 0; i < length / sizeof(uint32_t); i++) {
            d[i] = s[i];
            s[i] = 0;
        }
    }
    else
    {
        uint8_t * d = (uint8_t*)destination;
        uint8_t * s = (uint8_t*)source;

        for (i = 0; i < length; i++) {
            d[i] = s[i];
            s[i] = 0;
        }
    }

    return destination;
}

void displayRegs(uint64_t* exregs) {
    moveGlobalCursor(0, 0);
    for(int i=0;i<16;i++){
        gPrint(regs[i]);
        gPrint("0x");
        gPrintHex(exregs[i]);
        gPrint("\n");
    }
    gPrint(regs[16]); // imprime la direccion en donde ocurrio la exception aparte
    gPrint("0x");
    gPrintHex(exregs+18);
}
