#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>
#include <system.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define UP 8
#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define MAXSNAKELENGHT 300
#define GROWRATE 10
#define TICTAC_RADIUS 8
#define HEADRADIUS 4

typedef struct snake{
    int snakepos [2][MAXSNAKELENGHT];
    int dir;
    int lenght;
    int score;
}snakey;

typedef struct food{
    int x;
    int y;
    int radius;
}food;

typedef struct game{
    snakey s1;
    snakey s2;
    food food;
} game;

static uint32_t seed = 12345; // Initial seed value

// Custom random number generator function
uint32_t customRandom() {
    // LCG parameters (you can experiment with different values)
    uint32_t a = 1664525;
    uint32_t c = 1013904223;

    seed = (a * seed + c); // Update the seed value
    return seed;
}


void drawtictac(game* g){
    drawCircle(WHITE,g->food.x,g->food.y,g->food.radius);
}

void initgame(game * g){
g->s1.snakepos[0][0]=SCREEN_WIDTH/2;
g->s1.snakepos[1][0]=SCREEN_HEIGHT/2;
g->s1.lenght=40;
g->s1.dir=LEFT;
g->s1.score=0;

g->food.x=SCREEN_WIDTH/4;
g->food.y=SCREEN_HEIGHT/4;
g->food.radius=8;
}

void gameover(){
    printFormat("Press any key to go back to terminal \n");
    swapBuffer();
    while(!getChar());
}
int checksnakecolission(snakey *s){ // agregar condicion de choque para la otra snek
    if(s->snakepos[0][0]<0 || s->snakepos[0][0]>SCREEN_WIDTH || s->snakepos[1][0]<0 || s->snakepos[1][0]>SCREEN_HEIGHT)
        return 1;
    for(int i=1;i<s->lenght;i++)
        if(s->snakepos[0][0]==s->snakepos[0][i] && s->snakepos[1][0]==s->snakepos[1][i])
            return 1;
    return 0;
}

void checkfoodcolission(snakey *s,food *f){
    int i;
    if((s->snakepos[0][0] + HEADRADIUS >= f->x - f->radius && s->snakepos[0][0] + HEADRADIUS <= f->x + f->radius || (s->snakepos[0][0] - HEADRADIUS >= f->x - f->radius && s->snakepos[0][0] - HEADRADIUS <= f->x + f->radius)) && (s->snakepos[1][0] + HEADRADIUS >=f->y-f->radius && s->snakepos[1][0] + HEADRADIUS <=f->y+f->radius||(s->snakepos[1][0] - HEADRADIUS >=f->y-f->radius && s->snakepos[1][0] - HEADRADIUS <=f->y+f->radius))){
        s->lenght+=GROWRATE;
        f->x=customRandom()%SCREEN_WIDTH;
        f->y=customRandom()%SCREEN_HEIGHT;
        play_beep(2000, 100);
        s->score++;
    }
}

void drawsnake(snakey * s){
    for (int i=0;i<s->lenght;i++){
        drawCircle(RED,s->snakepos[0][i],s->snakepos[1][i],HEADRADIUS);
    }
}
char updateSnake(snakey * s){
    char c;
    if(keyPress()){
    c=getChar();
    c=c>='a' && c<='z' ? c : c+'a'-'A';
    switch (c){
        case 'w':
            if(s->dir!=DOWN)
                s->dir = UP;
            break;
        case 's':
            if(s->dir!=UP)
            s->dir = DOWN;
            break;
        case 'a':
            if(s->dir!=RIGHT)
            s->dir = LEFT;
            break;
        case 'd':
            if(s->dir!=LEFT)
            s->dir = RIGHT;
            break;
        default:
            break;
         }
    }
    else
        c=0;
    return c;
}

void moveSnake(snakey *s){
    for(int i=s->lenght-1;i>=1;i--){
        s->snakepos[0][i]=s->snakepos[0][i-1];
        s->snakepos[1][i]=s->snakepos[1][i-1];
    }
    switch (s->dir){
        case UP:
            s->snakepos[1][0]--;
            break;
        case DOWN:
            s->snakepos[1][0]++;
            break;
        case LEFT:
            s->snakepos[0][0]--;
            break;
        case RIGHT:
            s->snakepos[0][0]++;
            break;
        default:
            break;
    }
}
void drawscore(game *g){
    if(g->s1.score>9)
        drawNumber(500,20,60,WHITE,20,5,g->s1.score/10);
    drawNumber(540,20,60,WHITE,20,5,g->s1.score%10);
}
void snakegame(){
    food food;
    snakey s1;
    snakey s2;
    game game;

    game.s1=s1;
    game.s2=s2;
    game.food=food;

    initgame(&game);
    swapBuffer();

    char c1=0;
    int gm1=0;
    while(c1!=27 && gm1==0){
        c1=updateSnake(&game.s1);
        moveSnake(&game.s1);
        drawsnake(&game.s1);
        gm1=checksnakecolission(&game.s1);
        checkfoodcolission(&game.s1,&game.food);
        drawtictac(&game);
        drawscore(&game);
        swapBuffer();
    }
    gameover();

}
