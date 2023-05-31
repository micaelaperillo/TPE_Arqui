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
#define BARSPEED 5


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
    uint32_t width;
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
    g->ball.xDir = -1;
    g->ball.yDir = -1;

    // user settings
    g->user.v_bar.x = BAR_WIDTH;
    g->user.v_bar.y = SCREEN_HEIGHT/2 - BAR_HEIGHT*2;
    g->user.v_bar.height = BAR_HEIGHT;

    // computer settings
    g->computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    g->computer.v_bar.y = SCREEN_HEIGHT/2 + BAR_HEIGHT/2;
    g->computer.v_bar.width = BAR_WIDTH;
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


void check_entity_collision(player* p, ball* b) {
    uint32_t ball_next_pos_y = b->y + (b->yDir * (BALLSPEED + b->radius));
    uint32_t ball_next_pos_x = b->x + (b->xDir * (BALLSPEED + b->radius));
    if (ball_next_pos_y <= p->v_bar.y && ball_next_pos_y >= p->v_bar.y + p->v_bar.height
    && ball_next_pos_x >= p->v_bar.x && ball_next_pos_x <= p->v_bar.x + p->v_bar.width) {
        //collision detected
        b->xDir = -b->xDir;
        return;
    }
}

void update_ball(game* g) {
    // check collisions with vertical borders
    uint32_t nextY = g->ball.y + (g->ball.yDir * (SPEED_BALL + g->ball.radius));
    if (nextY <= 0) {
        g->ball.yDir = (g->ball.yDir < 0)?(-g->ball.yDir):(g->ball.yDir);
    } else if (nextY >= SCREEN_HEIGHT) {
        g->ball.yDir = (g->ball.yDir > 0)?(-g->ball.yDir):(g->ball.yDir);
    }

    //check collisions with players
    if(g->ball.xDir > 0) {
        //can only collide with the computer
        check_entity_collision(&g->computer, &g->ball);
    }
    else {
        //can only collide with the player
        check_entity_collision(&g->user, &g->ball);
    }

    //check if it reached the end
    if (g->ball.x + (g->ball.xDir * BALLSPEED) - g->ball.radius <= 0) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        //GOL COMPUTADORA
    } else if (g->ball.x + (g->ball.xDir * BALLSPEED) + g->ball.radius >= SCREEN_WIDTH) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        //GOL JUGADOR
    }

    g->ball.x += g->ball.xDir * BALLSPEED;
    g->ball.y += g->ball.yDir * BALLSPEED;
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
            // middle line


            //UPDATES POS

            //upp
            //uap

            drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);
            draw_bar(&game.computer.v_bar);
            draw_bar(&game.user.v_bar);
            update_ball(&game);
            draw_ball(&game.ball);
            swapBuffer();
     if (game.ball.y < game.computer.v_bar.y)
         move_bar(&game.computer.v_bar, -BARSPEED);
    else if(game.ball.y>game.computer.v_bar.y)
         move_bar(&game.computer.v_bar, BARSPEED);
    }

}
