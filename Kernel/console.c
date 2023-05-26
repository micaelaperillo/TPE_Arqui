#include <stdint.h>
#include <console.h>
#include <videoDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void scrollUp();

static char buffer[64] = { '0' };
static uint32_t consoleCursor = 0;
uint32_t width = 0;
uint32_t height = 0;

void initializeConsole() {
    width = getXCharSlots();
    height = getYCharSlots();
    cPrint("[Console initialized]");
    cNewline();

}

void cPrint(const char * string)
{
    int i;

    for (i = 0; string[i] != 0; i++)
        cPrintChar(string[i]);
}

void cPrintChar(char character)
{
    if(consoleCursor >= width || character == '\n') {
        cNewline();
        return;
    }
    putCharAt(consoleCursor, height, character);
    consoleCursor++;
}

void cNewline()
{
    scrollUp();
    consoleCursor = 0;
}

void cPrintDec(uint64_t value)
{
    cPrintBase(value, 10);
}

void cPrintHex(uint64_t value)
{
    cPrintBase(value, 16);
}

void cPrintBin(uint64_t value)
{
    cPrintBase(value, 2);
}

void cPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    cPrint(buffer);
}

void cErase() {
    if(consoleCursor > 0) {
        consoleCursor--;
        putCharAt(consoleCursor, height, ' ');
    }
}

void cClear()
{
    int i;

    for (i = 0; i < height * width; i++) {
        uint32_t xPos = i % width;
        uint32_t yPos = i / width;
        putCharAt(xPos, yPos, ' ');
    }
    consoleCursor = 0;
}

void scrollUp() {
    scrollCharArea();
}

//TODO mover uintToBase a una libreria aparte (utils.h?)
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    //Calculate characters for each digit
    do
    {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    }
    while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}
