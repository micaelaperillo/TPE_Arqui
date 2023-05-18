#include <stdint.h>
#include <console.h>
#include <videoDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint32_t cursor = 0;
static const uint32_t width = 78;
static const uint32_t height = 45;

void cPrint(const char * string)
{
    int i;

    for (i = 0; string[i] != 0; i++)
        cPrintChar(string[i]);
}

void cPrintChar(char character)
{
    uint32_t xPos = cursor % width;
    uint32_t yPos = cursor / width;
    putCharAt(xPos, yPos, character);
    cursor++;
}

void cNewline()
{
    do
    {
        cPrintChar(' ');
    }
    while(cursor % width != 0);
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

void cClear()
{
    int i;

    for (i = 0; i < height * width; i++) {
        uint32_t xPos = i % width;
        uint32_t yPos = i / width;
        putCharAt(xPos, yPos, ' ');
    }
    cursor = 0;
}

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
