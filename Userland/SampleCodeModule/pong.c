#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>
#include <system.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20
#define BALL_R 10
#define BALLSPEED 3
#define BARSPEED 2
#define OFFSET 2


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
    g->ball.xDir = 1;
    g->ball.yDir = 1;

    // user settings
    g->user.v_bar.x = 0;
    g->user.v_bar.y = SCREEN_HEIGHT/2 - BAR_HEIGHT*2;
    g->user.v_bar.width = BAR_WIDTH;
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
    drawRectangle(BLUE, b->x, b->y, b->width, b->height);
}

void draw_score(game* g) {
    drawNumber(420,200,60,WHITE,20,5,g->computer.score);
    drawNumber(580,200,60,WHITE,20,5,g->user.score);
}


void check_entity_collision(player* p, ball* b) {
    uint32_t ball_next_pos_y = b->y + (b->yDir * (BALLSPEED + b->radius));
    uint32_t ball_next_pos_x = b->x + (b->xDir * (BALLSPEED + b->radius));
    if (ball_next_pos_y >= p->v_bar.y && ball_next_pos_y <= p->v_bar.y + p->v_bar.height
    && ball_next_pos_x >= p->v_bar.x && ball_next_pos_x <= p->v_bar.x + p->v_bar.width) {
        //collision detected
        b->xDir = -b->xDir;
    }
}

void update_ball(game* g) {
    // check collisions with vertical borders
    uint32_t nextY = g->ball.y + (g->ball.yDir * (BALLSPEED + g->ball.radius));
    uint32_t nextX = g->ball.x + (g->ball.xDir * (BALLSPEED + g->ball.radius));
    if (nextY <= 0) {
        g->ball.yDir = (g->ball.yDir < 0)?(-g->ball.yDir):(g->ball.yDir);
    } else if (nextY >= SCREEN_HEIGHT) {
        g->ball.yDir = (g->ball.yDir > 0)?(-g->ball.yDir):(g->ball.yDir);
    }

    check_entity_collision(&g->user, &g->ball);
    check_entity_collision(&g->computer, &g->ball);

    //check if it reached the end
    if (g->ball.x + (g->ball.xDir * BALLSPEED) <= 0) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        g->computer.score++;
        //GOL COMPUTADORA
    } else if (g->ball.x + (g->ball.xDir * BALLSPEED) >= SCREEN_WIDTH) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        g->user.score++;
        //GOL JUGADOR
    }

    g->ball.x += g->ball.xDir * BALLSPEED;
    g->ball.y += g->ball.yDir * BALLSPEED;
}

void update_player_computer(game* g) {
    if(g->ball.y > g->computer.v_bar.y + (g->computer.v_bar.height / 2) + OFFSET) {
        g->computer.v_bar.y += BARSPEED;
    }else if(g->ball.y < g->computer.v_bar.y + (g->computer.v_bar.height / 2) + OFFSET) {
        g->computer.v_bar.y -= BARSPEED;
    }
}

void pong() {

    play_beep(2000, 80);

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
    while(c!=27) {
        if (keyPress()) {
            c = getChar();
            if (c == 'w' || c == 'W')
                game.user.v_bar.y -= BARSPEED;
            else if (c == 's' || c == "S")
                game.user.v_bar.y += BARSPEED;
        }


        //UPDATES POS

        //upp
        //uap

        update_player_computer(&game);
        update_ball(&game);
        drawRectangle(WHITE, SCREEN_WIDTH / 2, 0, 2, SCREEN_HEIGHT);
        draw_bar(&game.computer.v_bar);
        draw_bar(&game.user.v_bar);
        draw_ball(&game.ball);
        draw_score(&game);
        swapBuffer();
    }
}
