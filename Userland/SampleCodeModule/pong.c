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
#define SPEED 5
#define SPEED_BALL 1

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
    uint32_t ball_next_pos_y = b->y + (b->yDir * (SPEED_BALL + b->radius));
    uint32_t ball_next_pos_x = b->x + (b->xDir * (SPEED_BALL + b->radius));
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
    if (g->ball.x + (g->ball.xDir * SPEED_BALL) - g->ball.radius <= 0) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        //GOL COMPUTADORA
    } else if (g->ball.x + (g->ball.xDir * SPEED_BALL) + g->ball.radius >= SCREEN_WIDTH) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        //GOL JUGADOR
    }

    g->ball.x += g->ball.xDir * SPEED_BALL;
    g->ball.y += g->ball.yDir * SPEED_BALL;
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

    while(1) {

        if (keyPress()) {

            char c = getChar();
            switch (c)
            {
            case 'w':
                // moves up
                game.user.v_bar.y -= SPEED;
                break;
            case 'W':
                // moves up
                game.user.v_bar.y -= SPEED;
                break;
            case 's':
                // moves down
                game.user.v_bar.y += SPEED;
                break;
            case 'S':
                // moves down
                game.user.v_bar.y += SPEED;
                break;

            default:
                break;
            }
            // middle line
        }
            drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);
            draw_bar(&game.computer.v_bar);
            draw_bar(&game.user.v_bar);
            update_ball(&game);
            draw_ball(&game.ball);
            swapBuffer();

    }


    // while ((c = getChar) != 27) {

    //     // TODO definir alguna tecla (esc por ejemplo) que haga que corte el juego

    //     // TODO: que detecte la W y S
    //     if (keyPress()) {
    //         move_user_bar(&game.user.v_bar);
    //     }

    //     move_ball(&game.ball);
    //     // draw_ball(game.ball);

    //     // move the computer bar
    //     if (game.ball.y < SCREEN_HEIGHT/2) {
    //     // moves up if the ball is in the upper middle of the screen
    //         move_bar(game.computer.v_bar, -1);
    //     } else {
    //         // moves down otherwise
    //         move_bar(game.computer.v_bar, 1);
    //     }

    //     if (game.ball.x == game.user.v_bar.x) {
    //         if (!ball_touches_bar(game.ball, game.user.v_bar)) {
    //             // point for computer
    //             game.computer.score++;
    //             init_game_and_draw(game);
    //         }
    //     }
    //     if (game.ball.x == game.computer.v_bar.x) {
    //         if (!ball_touches_bar(game.ball, game.computer.v_bar)) {
    //         // point for user
    //             game.user.score++;
    //             init_game_and_draw(game);
    //         }
    //     }

    //     // draw rec and circle
    //     draw_ball(game.ball);
    //     draw_bar(game.user.v_bar);
    //     draw_bar(game.computer.v_bar);

    //     swapBuffer();
    // }

}
