#include <bitmapFont.h>
#include <stdint.h>

/*
//##
//Taken from https://wiki.osdev.org/VESA_Video_Modes
struct VbeInfoBlock {
    char VbeSignature[4];             // == "VESA"
    uint16_t VbeVersion;                 // == 0x0300 for VBE 3.0
    uint16_t OemStringPtr[2];            // isa vbeFarPtr
    uint8_t Capabilities[4];
    uint16_t VideoModePtr[2];         // isa vbeFarPtr
    uint16_t TotalMemory;             // as # of 64KB blocks
} __attribute__((packed));

VbeInfoBlock *vib = dos_alloc(512);
v86_bios(0x10, {ax:0x4f00, es:SEG(vib), di:OFF(vib)}, &out);
if (out.ax!=0x004f) die("Something wrong with VBE get info");

//##

 */

static const unsigned int width = 320, height = 200;
static uint8_t *video = (uint8_t*) 0xB8000;


void drawPixel(unsigned int x, unsigned int y, uint32_t color) {
    if(x > width || y > height) {
        return;
    }
    
}
