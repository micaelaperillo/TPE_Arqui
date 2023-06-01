#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>
#include <system.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20
#define BALL_R 10
#define BALLSPEED 1
#define BARSPEED 6
#define OFFSET 30


typedef struct {
    int x;
    int y;
    int xDir;
    int yDir;
    int radius;
} ball;

typedef struct {
    // (x,y) are the upper right coordinates
    // h is the height of the bar, the other two coordinates are (x1, y1+height) and (x2,y2+height)
    // (0,0) is the top left of the screen
    int x;
    int y;
    int height;
    int width;
    uint8_t dir;
} bar;

typedef struct {
    bar v_bar;
    int score;
} player;

typedef struct
{
    player user;
    player computer;
    ball ball;
} game;

void draw_bar(bar* b);
void draw_ball(ball* b);

void init_game_and_draw(game* g) {

    // middle line
    drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);

    // ball settings
    g->ball.x = SCREEN_WIDTH / 2;
    g->ball.y = SCREEN_HEIGHT / 2;
    g->ball.radius = BALL_R;
    g->ball.xDir = BALLSPEED * 2;
    g->ball.yDir = BALLSPEED;

    // user settings
    g->user.v_bar.x = 0;
    g->user.v_bar.y = SCREEN_HEIGHT/2 - BAR_HEIGHT*2;
    g->user.v_bar.width = BAR_WIDTH;
    g->user.v_bar.height = BAR_HEIGHT;
    g->user.v_bar.dir = 0;

    // computer settings
    g->computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    g->computer.v_bar.y = SCREEN_HEIGHT/2 + BAR_HEIGHT/2;
    g->computer.v_bar.width = BAR_WIDTH;
    g->computer.v_bar.height = BAR_HEIGHT;
    g->computer.v_bar.dir = 0;

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

void ball_impulse(ball* b, uint8_t dir) {
    if(b->yDir * dir < 0) {
        if( b->yDir == BALLSPEED ||  b->yDir == -BALLSPEED) {
            b->yDir = -b->yDir;
            return;
        }else {
            b->yDir += (b->yDir > 0)?(-BALLSPEED):(BALLSPEED);
            return;
        }
    }
    if(b->yDir * dir > 0) {
        b->yDir += (b->yDir > 0)?(BALLSPEED):(-BALLSPEED);;
        return;
    }

}

void check_entity_collision(player* p, ball* b) {
    int mult = ((int)b->xDir > 0)?(1):(-1);
    int ball_next_pos_y = b->y + BALLSPEED * b->yDir + b->radius * mult;
    int ball_next_pos_x = b->x + BALLSPEED * b->xDir + b->radius * mult;
    if (((ball_next_pos_y + b->radius >= p->v_bar.y && ball_next_pos_y + b->radius <= p->v_bar.y + p->v_bar.height) ||
    (ball_next_pos_y - b->radius >= p->v_bar.y && ball_next_pos_y - b->radius <= p->v_bar.y + p->v_bar.height))
    && ball_next_pos_x >= p->v_bar.x && ball_next_pos_x <= p->v_bar.x + p->v_bar.width) {
        //collision detected
        b->xDir = -b->xDir;
        ball_impulse(b, p->v_bar.dir);
    }
}

void update_ball(game* g) {
    // check collisions with vertical borders
    int mult = ((int) g->ball.xDir > 0)?(1):(-1);
    int nextY = g->ball.y + BALLSPEED * (int) g->ball.xDir + g->ball.radius * mult;
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
        g->computer.v_bar.dir = 1;
    }else if(g->ball.y < g->computer.v_bar.y + (g->computer.v_bar.height / 2) + OFFSET) {
        g->computer.v_bar.y -= BARSPEED;
        g->computer.v_bar.dir = -1;
    }else {
        g->computer.v_bar.dir = 0;
    }
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
    while(c!=27) {
        if (keyPress()) {
            c = getChar();
            if (c == 'w' || c == 'W') {
                game.user.v_bar.y -= BARSPEED;
                game.user.v_bar.dir = -1;
            }
            else if (c == 's' || c == "S") {
                game.user.v_bar.y += BARSPEED;
                game.user.v_bar.dir = 1;
            }
            else if(c == 27) {
                break;
            }
            else {
                game.user.v_bar.dir = 0;
            }
        } else {
            game.user.v_bar.dir = 0;
        }


        //UPDATES POS
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
