#include <stdint.h>
#include <standardLib.h>
// #include <sound.h>
#include <graphics.h>
#include <system.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20
#define BALL_R 15
#define BALLSPEED 1
#define BARSPEED 1


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
    // (0,0) is the top left of the screen
    uint32_t x;
    uint32_t y;
    uint32_t height;
} bar;

typedef struct {
    bar v_bar;
    uint32_t score;
} player;

typedef struct
{
    player user;
    player computer;
    ball ball;
} game;

void init_game_and_draw(game* g) {

    // middle line
    drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);

    // ball settings
    g->ball.x = SCREEN_WIDTH / 2;
    g->ball.y = SCREEN_HEIGHT / 2;
    g->ball.radius = BALL_R;
    g->ball.xDir = 1;
    g->ball.yDir = 1;

    // user settings
    g->user.v_bar.x = BAR_WIDTH;
    g->user.v_bar.y = SCREEN_HEIGHT/2 - BAR_HEIGHT*2;
    g->user.v_bar.height = BAR_HEIGHT;

    // computer settings
    g->computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    g->computer.v_bar.y = SCREEN_HEIGHT/2 + BAR_HEIGHT/2;
    g->computer.v_bar.height = BAR_HEIGHT;

    draw_bar(&g->user.v_bar);
    draw_bar(&g->computer.v_bar);
    draw_ball(&g->ball);


    swapBuffer();

}

void draw_ball(ball* b) {
    drawCircle(WHITE, b->x, b->y, b->radius);
}

void draw_bar(bar *b) {
    drawRectangle(BLUE, b->x, b->y, BAR_WIDTH, BAR_HEIGHT);
}

void draw_score(game g) {
    // TODO
}

void move_ball(ball * b) {

    // draws black circle on top of old ball
    drawCircle(BLACK, b->x, b->y, b->radius);

    b->x += b->xDir;
    b->y += b->yDir;

    // check collisions
    if (b->x + b->xDir - b->radius <= 0) {
        b->xDir = (b->xDir < 0)?(-b->xDir):(b->xDir);
    } else if (b->x + b->xDir + b->radius >= SCREEN_WIDTH) {
        b->xDir = (b->xDir > 0)?(-b->xDir):(b->xDir);
    }

    if (b->y + b->yDir - b->radius <= 0) {
        b->yDir = (b->yDir < 0)?(-b->yDir):(b->yDir);
    } else if (b->y + b->yDir + b->radius >= SCREEN_HEIGHT) {
        b->yDir = (b->yDir > 0)?(-b->yDir):(b->yDir);
    }

    // Draw the new ball at the updated position
    drawCircle(BLUE, b->x, b->y, b->radius);

}

void move_bar(bar *b, uint32_t y) {
    if (b->y + y * BARSPEED < 0 || b->y + y * BARSPEED > SCREEN_HEIGHT) {
        y = y * -1;
    }
    b->y += y * BARSPEED;
    draw_bar(b);

    // y = -1 --> moves up
    // y = 1 --> moves down
}

uint32_t ball_touches_bar(ball *ball, bar *bar) {
    if (ball->x != bar->x) {
        return 0;
    }

    // verify that the ball is inside the bar dims
    if ((ball->y <= bar->y + bar->height) && (ball->y >= ball->y)) {
        // TODO add beep
        // play_beep();
        return 1;
    }
    return 0;
}

void pong() {

    // USER: left, COMPUTER: right

    player user, computer;
    ball ball;
    game game;

    game.ball = ball;
    game.user = user;
    game.computer = computer;

    game.user.score = 0;
    game.computer.score = 0;

    // draws
    init_game_and_draw(&game);
    char c;
    while(1) {
        if (keyPress()) {
            c = getChar();
            if(c=='w'||c=='W')
                game.user.v_bar.y -= BARSPEED;
            else if(c=='s'||c=="S")
                game.user.v_bar.y += BARSPEED;
            }


            //UPDATES POS

            //upp
            //uap

            drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);
            draw_bar(&game.computer.v_bar);
            draw_bar(&game.user.v_bar);
            move_ball(&game.ball);
            draw_ball(&game.ball);
            swapBuffer();

    if (game.ball.y < game.computer.v_bar.y)
        // -1 si sube
        move_bar(&game.computer.v_bar, -BARSPEED);
    else if(game.ball.y > game.computer.v_bar.y)
        // 1 si baja
        move_bar(&game.computer.v_bar, BARSPEED);
    }

}
