#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <console.h>
#include <videoDriver.h>

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

void updateBubblePosition(int* x, int* y, int* xDir, int* yDir, int width) {
    if(*x + *xDir - width <= 0) {
        *xDir = (*xDir < 0)?(-*xDir):(*xDir);
    } else if(*x + *xDir + width >= 1024) {
        *xDir = (*xDir > 0)?(-*xDir):(*xDir);
    }
    if(*y + *yDir - width <= 0) {
        *yDir = (*yDir < 0)?(-*yDir):(*yDir);
    } else if(*y + *yDir + width >= 768) {
        *yDir = (*yDir > 0)?(-*yDir):(*yDir);
    }
    *x += *xDir;
    *y += *yDir;
}

void screenSaver() {
    enableDoubleBuffering();
    int x1=40, x2=60, x3=600, x4=460, x5=510, x6=30;
    int y1=360, y2=0, y3=700, y4=500, y5=80, y6=600;
    int xDir1=1, xDir2=2, xDir3=3, xDir4=1, xDir5=3, xDir6=2;
    int yDir1=3, yDir2=2, yDir3=2, yDir4=2, yDir5=1, yDir6=1;
    int width = 20;
    //TODO cambiar para que termine cuando detecta input

    while(1) {

        updateBubblePosition(&x1, &y1, &xDir1, &yDir1, width);
        updateBubblePosition(&x2, &y2, &xDir2, &yDir2, width);
        updateBubblePosition(&x3, &y3, &xDir3, &yDir3, width);
        updateBubblePosition(&x4, &y4, &xDir4, &yDir4, width);
        updateBubblePosition(&x5, &y5, &xDir5, &yDir5, width);
        updateBubblePosition(&x6, &y6, &xDir6, &yDir6, width);

        drawColoredCircle(RED, x1, y1, width);
        drawColoredCircle(GREEN, x2, y2, width);
        drawColoredCircle(BLUE, x3, y3, width);
        drawColoredCircle(YELLOW, x4, y4, width);
        drawColoredCircle(PINK, x5, y5, width);
        drawColoredCircle(CYAN, x6, y6, width);

        drawBuffer();
    }
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
	cNewline();
	cPrint("[Finished]");
    //screenSaver();
	return 0;
}
