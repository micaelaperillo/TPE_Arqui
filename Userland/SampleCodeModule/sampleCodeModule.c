/* sampleCodeModule.c */
#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>
#include <commands.h>
#include <shell.h>


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
    //Lo mismo pero con graphics.h
    drawEmptyRectangle(WHITE, 900, 600, 10, 50);

    startShell();

    return 0;
}
