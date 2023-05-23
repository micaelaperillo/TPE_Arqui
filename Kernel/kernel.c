#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <console.h>
#include <videoDriver.h>
#include <keyboard.h>

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


//TODO mover todas las funciones de bubble a userspace cuando lo tengamos implementado
struct Bubble {
    int x, y;
    int xDir, yDir;
    int width;
    Color c;
}Bubble;

void updateBubblePosition(struct Bubble *bubble) {
    if(bubble->x + bubble->xDir - bubble->width <= 0) {
        bubble->xDir = (bubble->xDir < 0)?(-bubble->xDir):(bubble->xDir);
    } else if(bubble->x + bubble->xDir + bubble->width >= 1024) {
        bubble->xDir = (bubble->xDir > 0)?(-bubble->xDir):(bubble->xDir);
    }
    if(bubble->y + bubble->yDir - bubble->width <= 0) {
        bubble->yDir = (bubble->yDir < 0)?(-bubble->yDir):(bubble->yDir);
    } else if(bubble->y + bubble->yDir + bubble->width >= 768) {
        bubble->yDir = (bubble->yDir > 0)?(-bubble->yDir):(bubble->yDir);
    }
    bubble->x += bubble->xDir;
    bubble->y += bubble->yDir;
}

void drawBubble(struct Bubble bubble) {
    drawEmptyColoredCircle(bubble.c, bubble.x, bubble.y, bubble.width);
}

void screenSaver() {
    enableDoubleBuffering();
    int size = 21;
    struct Bubble bbs[] = {{100, 0, 1, 3, 20, WHITE},  {500, 10, 2, 1, 20, RED},  {1000, 50, 2, 2, 20, BLUE},  {800, 125, -2, 1, 20, YELLOW},
                             {100, 700, -1, -3, 20, CYAN}, {9, 700, 2, -1, 20, GREEN}, {100, 700, -1, -3, 20, PINK},
                           {100, 768, -2, 2, 20, WHITE},  {5, 10, 2, -3, 20, RED},  {370, 500, 2, -2, 20, BLUE},  {1200, 600, 2, -1, 20, YELLOW},
                           {100, 300, -1, 3, 20, CYAN}, {90, 70, -3, 1, 20, GREEN}, {1000, 700, -1, -2, 20, PINK},
            {1000, 50, -3, 1, 20, WHITE},  {5, 10, 2, -2, 20, RED},  {100, 100, 2, -1, 20, BLUE},  {1200, 620, 2, -2, 20, YELLOW},
            {100, 367, -3, 2, 20, CYAN}, {990, 701, -2, -1, 20, GREEN}, {150, 610, -1, -1, 20, PINK}};
    //TODO cambiar para que termine cuando detecta input
    int i;
    while(1) {

        for(i = 0; i<size; i++) {
            updateBubblePosition(&bbs[i]);
            drawBubble(bbs[i]);
        }

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
	return 0;
}
