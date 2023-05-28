#include <stdint.h>
#include <keyboard.h>
#include <sound.h>
#include <graphics.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20

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


void pong() {

    player user, computer;

    setPlayer(&user);
    setPlayer(&computer);

    ball ball;

    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;

    // USER: left, COMPUTER: right
    user.v_bar.x = BAR_WIDTH;
    user.v_bar.y = (SCREEN_HEIGHT/2) + BAR_HEIGHT/2;
    user.v_bar.height = BAR_HEIGHT;

    computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    computer.v_bar.y = (SCREEN_HEIGHT/2) + BAR_HEIGHT/2;
    computer.v_bar.height = BAR_HEIGHT;

    user.score = 0;
    computer.score = 0;

    game game;

    game.ball = ball;
    game.user = user;
    game.computer = computer;

    while (1) {

        // draws 
        init_draw(game);

        // TODO: no estoy muy segura de la logica del handle_moves y move_ball, no se si estan en el orden correcto
        handle_moves(&user.v_bar);
        move_ball(&game.ball);

        if (game.ball.x == game.user.v_bar.x) {
            if (!ball_touches_bar(game.ball, game.user.v_bar)) {
                // point for computer
                game.computer.score++;
                init_draw(game);
            }
        }
        if (game.ball.x == game.computer.v_bar.x) {
            if (!ball_touches_bar(game.ball, game.computer.v_bar)) {
                // point for user
                game.user.score++;
                init_draw(game);
            }
        }
    }
}


void init_draw(game g) {
    drawRectangle(0xFF, SCREEN_WIDTH/2, 0, 5, SCREEN_HEIGHT);

    g.ball.x = SCREEN_WIDTH / 2;
    g.ball.y = SCREEN_HEIGHT / 2;

    g.user.v_bar.x = BAR_WIDTH;
    g.user.v_bar.y = (SCREEN_HEIGHT/2) + BAR_HEIGHT/2;
    g.user.v_bar.height = BAR_HEIGHT;

    g.computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    g.computer.v_bar.y = (SCREEN_HEIGHT/2) + BAR_HEIGHT/2;
    g.computer.v_bar.height = BAR_HEIGHT;

    draw_bar(g.user.v_bar);
    draw_bar(g.computer.v_bar);
    draw_ball(g.ball);
    draw_score(g);

}

void draw_ball(ball b) {
    drawCircle(0xFF, b.x, b.y, b.radius);
}

void draw_bar(bar b) {
    drawRectangle(0xFF, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);
}

void draw_score(game g) {
    // TODO
}

void move_ball(ball * b) {

    // draws black circle on top of old ball
    drawCircle(0x00, b->x, b->y, b->radius);
    
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
    
    // draws new ball
    drawCircle(0xFF, b->x, b->y, b->radius);

} 

void handle_moves(bar * b) {
    // gets key with the keyboard driver
    // if key == W --> move_bar(&bar, -1)
    // if key == S --> move_bar(&bar, 1)
    // else --> no hace nada

    char c = getc();
    if (c == "w" || c == "W") {
        move_bar(*b, -1);
    } else if (c == "s" || c == "S") {
        move_bar(*b, 1);
    }
}

void move_bar(bar b, uint32_t y) {

    // draws black rectangle on top of the old bar
    drawRectangle(0x00, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);
    b.y+= y;
    drawRectangle(0xFF, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);


    // y = -1 --> moves up
    // y = 1 --> moves down
}

char ball_touches_bar(ball ball, bar bar) {
    if (ball.x != bar.x) {
        return 0;
    }

    // verify that the ball is inside the bar dims
    if ((ball.y <= bar.y + bar.height) && (ball.y >= ball.y)) {
        play_beep();
        return 1;
    }
    return 0;    
}