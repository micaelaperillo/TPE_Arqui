#include <stdint.h>
#include <standardLib.h>
// #include <sound.h>
#include <graphics.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20
#define BALL_R 15

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

void init_game_and_draw(game g) {

    // middle line
    drawRectangle(0xFF, SCREEN_WIDTH/2, 0, 5, SCREEN_HEIGHT);

    g.ball.x = SCREEN_WIDTH / 2;
    g.ball.y = SCREEN_HEIGHT / 2;
    g.ball.radius = BALL_R;
    g.ball.xDir = 1;
    g.ball.yDir = 1;

    g.user.v_bar.x = BAR_WIDTH;
    g.user.v_bar.y = (SCREEN_HEIGHT/2) - BAR_HEIGHT*2;
    g.user.v_bar.height = BAR_HEIGHT;
    g.user.score = 0;

    g.computer.v_bar.x = SCREEN_WIDTH - BAR_WIDTH;
    g.computer.v_bar.y = (SCREEN_HEIGHT/2) + BAR_HEIGHT/2;
    g.computer.v_bar.height = BAR_HEIGHT;
    g.computer.score = 0;

    draw_bar(g.user.v_bar);
    draw_bar(g.computer.v_bar);
    draw_ball(g.ball);
    draw_score(g);

}

void draw_ball(ball b) {
    drawCircle(0xFA, b.x, b.y, b.radius);
}

void draw_bar(bar b) {
    drawRectangle(0xFF, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);
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

void move_bar(bar b, uint32_t y) {

    // draws black rectangle on top of the old bar
    drawRectangle(BLACK, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);
    b.y += y;
    drawRectangle(BLUE, b.x, b.y, BAR_WIDTH, BAR_HEIGHT);


    // y = -1 --> moves up
    // y = 1 --> moves down
}

void handle_moves(game * g) {
    // gets key with the keyboard driver
    // if key == W --> move_bar(bar, -1)
    // if key == S --> move_bar(bar, 1)
    // else --> no hace nada

    char c = getChar();
    if (c == 'w' || c == 'W') {
        move_bar((g->user.v_bar), -1);
    } else if (c == 's' || c == 'S') {
        move_bar((g->user.v_bar), 1);
    }

}

uint32_t ball_touches_bar(ball ball, bar bar) {
    if (ball.x != bar.x) {
        return 0;
    }

    // verify that the ball is inside the bar dims
    if ((ball.y <= bar.y + bar.height) && (ball.y >= ball.y)) {
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

    // draws 
    init_game_and_draw(game);

    while (1) {

        // TODO definir alguna tecla (esc por ejemplo) que haga que corte el juego 
        // TODO: no estoy muy segura de la logica del handle_moves y move_ball, no se si estan en el orden correcto
        // TODO: que detecte la W y S 
        // if (keyPressed())
            handle_moves(&game);
        move_ball(&game.ball);
        draw_ball(game.ball);

        // move the computer bar
        if (game.ball.y < SCREEN_HEIGHT/2) {
        // moves up if the ball is in the upper middle of the screen                
            move_bar(game.computer.v_bar, -1);
        } else {
            // moves down otherwise
            move_bar(game.computer.v_bar, 1);
        }       
        
        if (game.ball.x == game.user.v_bar.x) {
            if (!ball_touches_bar(game.ball, game.user.v_bar)) {
                // point for computer
                game.computer.score++;
                init_game_and_draw(game);
                break;
            }
        }
        if (game.ball.x == game.computer.v_bar.x) {
            if (!ball_touches_bar(game.ball, game.computer.v_bar)) {
            // point for user
                game.user.score++;
                init_game_and_draw(game);
                break;
            }
        }
        swapBuffer();
    }
        
}