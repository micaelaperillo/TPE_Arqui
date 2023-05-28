#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t xDir;
    uint32_t yDir;
    uint32_t radius;
} ball;

typedef struct {
    // (x,y) are the upper right coordinates
    // h is the height of the bar, the other two coordinates are (x1, y1+height) and (x2,y2+height)
    // assuming (0,0) is the top left of the screen
    uint32_t x;
    uint32_t y;
    uint32_t height;
    uint32_t speed; // sleeps this amount of ms every move
} bar;

typedef struct {
    bar v_bar;
    uint32_t score;
} player;

int main() {

    player user, computer;

    setPlayer(&user);
    setPlayer(&computer);

    ball ball;

    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;

    // TODO: definir las (x,y) de las bar del user y la computer
    user.v_bar.x = 1;
    user.v_bar.y = 1;
    user.v_bar.height = BAR_HEIGHT;

    computer.v_bar.x = 1;
    computer.v_bar.y = 1;
    computer.v_bar.height = BAR_HEIGHT;

    while (1) {

        draw_background();
        draw_bar(user.v_bar);
        draw_bar(computer.v_bar);
        draw_ball(ball);
        draw_score(user.score, computer.score);
        // play game
    }

    

}

void setPlayer(player * p) {
    p->score = 0;
    // TODO: set the bar, i dont know the screen dim
}


void draw_background() {

}

void draw_ball(ball b) {
    // draws the ball in (x,y), stored in struct
}

void draw_bar(bar b) {
    
}

void draw_score(uint32_t user, uint32_t computer) {

}

void update_ball(ball * b) {
    
    if (b->x + b->xDir - b->radius <= 0) {
        b->xDir = (b->xDir < 0)?(-b->xDir):(b->xDir);
    } else if (b->x + b->xDir + b->radius >= 1024) {
        b->xDir = (b->xDir > 0)?(-b->xDir):(b->xDir);
    }

    if (b->y + b->yDir - b->radius <= 0) {
        b->yDir = (b->yDir < 0)?(-b->yDir):(b->yDir);
    } else if (b->y + b->yDir + b->radius >= 768) {
        b->yDir = (b->yDir > 0)?(-b->yDir):(b->yDir);
    }

    b->x += b->xDir;
    b->y += b->yDir;

} 

void handle_key() {
    // gets key with the keyboard driver
    // if key == W --> move_bar(&bar, -1)
    // if key == S --> move_bar(&bar, 1)
    // else --> no hace nada
}

void move_bar(bar * b, uint32_t y) {
    // y = -1 --> moves up
    // y = 1 --> moves down
}