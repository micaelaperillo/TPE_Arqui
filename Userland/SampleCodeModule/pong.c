#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>
#include <system.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BAR_HEIGHT 150
#define BAR_WIDTH 20
#define BALL_R 10
#define BALLSPEED 2
#define BARSPEED 8
#define IMPULSESPEED 1
#define OFFSET 50

typedef struct {
    int x;
    int y;
    int xDir;
    int yDir;
    int radius;
} ball;

typedef struct {
    int x;          // upper left x position
    int y;          // upper left y position
    int height;
    int width;
    int dir;
} bar;

typedef struct {
    bar v_bar;
    int score;
} player;

typedef struct {
    player user;
    player computer;
    ball ball;
} game;

// function prototypes
void draw_bar(bar * b);
void draw_ball(ball * b);
void init_game_and_draw(game* g);
void draw_score(game * g);
void ball_impulse(ball* b, int dir);
void check_entity_collision(player * p, ball * b);
void update_ball(game * g);
void update_player_computer(game * g);
void pong();

void init_game_and_draw(game * g) {

    // middle line
    drawRectangle(BLUE, SCREEN_WIDTH/2, 0, 2, SCREEN_HEIGHT);

    // ball settings
    g->ball.x = SCREEN_WIDTH / 2;
    g->ball.y = SCREEN_HEIGHT / 2;
    g->ball.radius = BALL_R;
    g->ball.xDir = BALLSPEED;
    g->ball.yDir = 1;

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

void draw_ball(ball * b) {
    drawCircle(WHITE, b->x, b->y, b->radius);
}

void draw_bar(bar * b) {
    drawRectangle(BLUE, b->x, b->y, b->width, b->height);
}

void draw_score(game * g) {
    drawNumber(420,200,60,WHITE,20,5,g->user.score);
    drawNumber(580,200,60,WHITE,20,5,g->computer.score);
}

void ball_impulse(ball * b, int dir) {
    if(dir == 0) {
        return;
    }
    if(dir * b->yDir < 0) {
        if(b->yDir - IMPULSESPEED == 0 || b->yDir + IMPULSESPEED == 0) {
            b->yDir = -b->yDir;
        }
        else {
            b->yDir += (b->yDir > 0) ? (-IMPULSESPEED) : (IMPULSESPEED);
        }
        return;
    } else{
        b->yDir += (b->yDir > 0)?(IMPULSESPEED):(-IMPULSESPEED);
        return;
    }
}

void check_entity_collision(player * p, ball * b) {
    int mult = (b->xDir > 0)?(1):(-1);
    int ball_next_pos_y = b->y + BALLSPEED * b->yDir + b->radius * mult;
    int ball_next_pos_x = b->x + BALLSPEED * b->xDir + b->radius * mult;
    if (((ball_next_pos_y + b->radius >= p->v_bar.y && ball_next_pos_y + b->radius <= p->v_bar.y + p->v_bar.height) ||
    (ball_next_pos_y - b->radius >= p->v_bar.y && ball_next_pos_y - b->radius <= p->v_bar.y + p->v_bar.height))
    && ball_next_pos_x >= p->v_bar.x && ball_next_pos_x <= p->v_bar.x + p->v_bar.width) {
        // collision detected
        b->xDir = -b->xDir;
        ball_impulse(b, p->v_bar.dir);
    }
}

void recenter_player(player * p) {
    if(p->v_bar.y < 0) {
        p->v_bar.y = 0;
    }else if(p->v_bar.y + p->v_bar.height > SCREEN_HEIGHT) {
        p->v_bar.y = SCREEN_HEIGHT - p->v_bar.height;
    }
}

void update_ball(game * g) {
    // check collisions with vertical borders
    int mult = (g->ball.yDir > 0)?(1):(-1);
    int nextY = g->ball.y + BALLSPEED * g->ball.yDir + g->ball.radius * mult;
    if (nextY <= 0) {
        g->ball.yDir = (g->ball.yDir < 0)?(-g->ball.yDir):(g->ball.yDir);
    } else if (nextY >= SCREEN_HEIGHT) {
        g->ball.yDir = (g->ball.yDir > 0)?(-g->ball.yDir):(g->ball.yDir);
    }

    check_entity_collision(&g->user, &g->ball);
    check_entity_collision(&g->computer, &g->ball);

    // check if it reached the end
    if (g->ball.x + (g->ball.xDir * BALLSPEED) <= 0) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        g->ball.yDir = 1;
        g->computer.score++;
        play_beep(2000, 100);
        // GOL COMPUTER
    } else if (g->ball.x + (g->ball.xDir * BALLSPEED) >= SCREEN_WIDTH) {
        g->ball.x = SCREEN_WIDTH / 2;
        g->ball.y = SCREEN_HEIGHT / 2;
        g->ball.xDir = -g->ball.xDir;
        g->ball.yDir = 1;
        g->user.score++;
        play_beep(2000, 100);
        // GOL USER
    }
    g->ball.x += g->ball.xDir * BALLSPEED;
    g->ball.y += g->ball.yDir * BALLSPEED;
}

void update_player_computer(game * g) {
    if(g->ball.x > SCREEN_WIDTH / 4 * 3 || g->ball.xDir > 0) {
        if (g->ball.y > g->computer.v_bar.y + (g->computer.v_bar.height / 2) + OFFSET) {
            g->computer.v_bar.y += BARSPEED;
            g->computer.v_bar.dir = 1;
        } else if (g->ball.y < g->computer.v_bar.y + (g->computer.v_bar.height / 2) - OFFSET) {
            g->computer.v_bar.y -= BARSPEED;
            g->computer.v_bar.dir = -1;
        } else {
            if (g->user.v_bar.dir != 0) {
                g->user.v_bar.y += (g->user.v_bar.dir > 0) ? (BARSPEED) : (-BARSPEED);
                g->user.v_bar.dir = 0;
            }
        }
        recenter_player(&g->computer);
    } else {
        //returns to the center of the screen
        if(g->computer.v_bar.y + (g->computer.v_bar.height / 2) < (SCREEN_HEIGHT / 2) - OFFSET
        || g->computer.v_bar.y + (g->computer.v_bar.height / 2) > (SCREEN_HEIGHT / 2) + OFFSET) {
            g->computer.v_bar.y += (g->computer.v_bar.y + (g->computer.v_bar.height / 2) > SCREEN_HEIGHT / 2) ? (-BARSPEED) : (BARSPEED);
        }

    }
}

uint8_t is_key(char c, char k) {
    char dist = 'a' - 'A';
    return c == k || c == k + dist;
}

char update_player_user(game* g) {
    char c;
    if (keyPress()) {
        c = getChar();
        if (is_key(c, 'w')) {
            g->user.v_bar.y -= BARSPEED;
            g->user.v_bar.dir = -1;
        }
        else if (is_key(c, 's')) {
            g->user.v_bar.y += BARSPEED;
            g->user.v_bar.dir = 1;
        }
        else {
            g->user.v_bar.dir = 0;
        }
    }
    else {
        //this creates smoother movement
        if(g->user.v_bar.dir!=0) {
            g->user.v_bar.y += (g->user.v_bar.dir > 0)?(BARSPEED):(-BARSPEED);
            g->user.v_bar.dir = 0;
        }
        c = 0;
    }
    recenter_player(&g->user);
    return c;
}

void welcome() {
    printFormat("\nWelcome to PONG. Press any key to start the game\n");
    swapBuffer();
    while (!getChar()) { }
}

void pause() {
    char c;
    while(!getChar()) { }
}

void pong() {

    welcome();

    // the USER is the bar on the left
    // the COMPUTER is the bar on the right

    player user = {};
    player computer = {};
    ball ball = {};
    game game;

    game.ball = ball;
    game.user = user;
    game.computer = computer;

    game.user.score = 0;
    game.computer.score = 0;

    // draws initial game
    init_game_and_draw(&game);
    char c = 0;
    while(c != 27 && (game.user.score != 3 && game.computer.score != 3)) {
        
        // pressing P pauses the game and unables double buffer
        if (c == 'p' || c == 'P') {
            printFormat("\nPress any key to return");
            swapBuffer();
            disableDoubleBuffering();
            pause();
            enableDoubleBuffering();
        }

        // UPDATES POS
        c = update_player_user(&game);
        update_player_computer(&game);
        update_ball(&game);

        // DRAWS FRAME
        drawRectangle(WHITE, SCREEN_WIDTH / 2, 0, 2, SCREEN_HEIGHT);
        draw_bar(&game.computer.v_bar);
        draw_bar(&game.user.v_bar);
        draw_ball(&game.ball);
        draw_score(&game);
        draw_score(&game);
        //invalidOp(); //for testing
        // SHOWS FRAME ON SCREEN
        swapBuffer();
    }

    if (game.user.score == 3) {
        // the winner is USER
        printFormat("\nWINNER: USER. Press ESC to return\n");
        swapBuffer();
    } else if (game.computer.score == 3) {
        // the winner is COMPUTER
        printFormat("\nWINNER: COMPUTER. Press ESC to return\n");
        swapBuffer();
    }

    while (getChar() != 27) {
        // returns when the user presses ESC    
    }
}