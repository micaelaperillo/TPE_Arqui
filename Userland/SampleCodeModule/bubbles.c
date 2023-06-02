#include <graphics.h>
#include <system.h>
#include <standardLib.h>

struct Bubble {
    int x, y;
    int xDir, yDir;
    int width;
    uint32_t c;
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
    drawEmptyCircle(bubble.c, bubble.x, bubble.y, bubble.width);
}

void bubbles() {
    int size = 21;
    struct Bubble bbs[] = {{100, 0, 1, 3, 20, WHITE},  {500, 10, 2, 1, 20, RED},  {1000, 50, 2, 2, 20, BLUE},  {800, 125, -2, 1, 20, YELLOW},
                           {100, 600, -1, -3, 20, CYAN}, {9, 700, 2, -1, 20, GREEN}, {100, 700, -1, -3, 20, PINK},
                           {100, 768, -2, 2, 20, WHITE},  {5, 10, 2, -3, 20, RED},  {370, 500, 2, -2, 20, BLUE},  {1200, 600, 2, -1, 20, YELLOW},
                           {100, 300, -1, 3, 20, CYAN}, {90, 70, -3, 1, 20, GREEN}, {1000, 700, -1, -2, 20, PINK},
                           {1000, 50, -3, 1, 20, WHITE},  {5, 10, 2, -2, 20, RED},  {100, 100, 2, -1, 20, BLUE},  {1200, 620, 2, -2, 20, YELLOW},
                           {100, 367, -3, 2, 20, CYAN}, {990, 701, -2, -1, 20, GREEN}, {150, 610, -1, -1, 20, PINK}};
    int i;
    char c;
    while(!keyPress() || (c=getChar()) != 27) {
        //runs until 'esc' is pressed
        //animation loop
        for(i = 0; i<size; i++) {
            updateBubblePosition(&bbs[i]);
            drawBubble(bbs[i]);
        }

        swapBuffer();//double buffering needs to be enabled previously
    }
}
