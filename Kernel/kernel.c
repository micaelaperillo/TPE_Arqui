#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <console.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <time.h>
#include <sound.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

//TODO esto es de testeo, despues deberia ir a una libreria aparte
extern void interrupt(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

void div(){
	int i=1/0;
}
int main()
{
    initializeConsole();
    cNewline();
	cPrint("[Kernel Main]");
    load_idt();
	cNewline();
	cPrint("  Sample code module at 0x");
	cPrintHex((uint64_t)sampleCodeModuleAddress);
	cNewline();
	cPrint("  Calling the sample code module returned: ");
	cPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	cNewline();
	cNewline();

	cPrint("  Sample data module at 0x");
	cPrintHex((uint64_t)sampleDataModuleAddress);
	cNewline();
	cPrint("  Sample data module contents: ");
	cPrint((char*)sampleDataModuleAddress);
	//div(); testeo la division por cero.Creo que es un testeo valido xd
	cNewline();


	char * time;
	char * date;
	timeToStr(time);
	cPrint(time);
	cNewline();
	dateToStr(date);
	cPrint(date);
	cNewline();

	play_beep();

	play_beep();

	play_beep();

	play_beep();

	play_beep();

	cPrint("[Finished]");

	return 0;
}
