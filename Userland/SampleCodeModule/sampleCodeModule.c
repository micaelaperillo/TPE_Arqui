/* sampleCodeModule.c */
#include <stdint.h>
#include <standardLib.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

int main() {

    //DIBUJA UN CUADRADO EN LA PANTALLA CON UNA SYS_CALL COMO EJEMPLO
    uint32_t x,y, width, height;
    uint64_t coord, wh;
    x = 500, y =300;
    height = 50, width = 30;
    coord = ((uint64_t) x << 32) | y;
    wh = ((uint64_t) height << 32) | width;
    interrupt(2, 3, coord, 0, wh, 0xFFFFFF);
    //Desupues lo pueden sacar

    return 0;
}