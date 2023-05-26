#include <stdint.h>
#include <standardLib.h>
#include <graphics.h>

//TODO los programas podrian estar en su propio archivo

// ################## PROGRAM DATA #####################
#define MAX_PROGRAMS 20
typedef void (*FunctionPtr)();

struct PROGRAM_STRUCT {
    char* name_id;
    char* description;
    FunctionPtr program;
}PROGRAM_STRUCT;

typedef struct PROGRAM_STRUCT Program;

Program pList[20];
static int pAmount = 0;

void help();

void setupProgram(char* name_id, char* description, FunctionPtr program) {
    //TODO lanzar excepcion si se pasa (?)
    if(pAmount < MAX_PROGRAMS){
        Program newProgram = {name_id, description, program};
        pList[pAmount++];
    }
}

void help() {
    //TODO : recorre pList e imprime los comandos y su descripcion
}
// ################## PROGRAM DATA #####################





// ################## CONSOLE #####################
#define SYS_CURSOR_ID 2

#define CONSOLE_X_DIM 96
#define CONSOLE_Y_DIM 47   // -1, as the last line is reserved for the command prompt

#define CONSOLE_DIM CONSOLE_Y_DIM * CONSOLE_Y_DIM

typedef char cLine[CONSOLE_X_DIM];

static cLine* console[CONSOLE_Y_DIM];
static cLine cPrompt;

static unsigned int cursor = 0;

void clearLine(int line);
void reprintLine(int line);
void reprintConsole();
void _moveCursor(unsigned long pos);
void swapLines();


void setupConsole() {
    //clears all the values
    for(int i=0; i<CONSOLE_Y_DIM; i++) {
        clearLine(i);
    }
}

void startShell() {
    //PROGRAMS SETUP
    setupProgram("help", "displays all available commands", help);

    //INITIALIZATIONS
    clearScreen();
    setupConsole();
    //STARTS THE CONSOLE
    putC('a');
}

void reprintConsole() {
    _moveCursor(0);
    for(int i=0; i<CONSOLE_Y_DIM; i++) {
        reprintLine(i);
    }
}

void _moveCursor(unsigned long pos) {
    interrupt(SYS_CURSOR_ID, pos, 0, 0 ,0, 0);
}

void _writeChar(char c) {
    //WRITES ONLY ON THE BOTTOM LINE, USED FOR WRITING TO THE CONSOLE
    //THIS FUNCTION REQUIRES THE CURSOR TO ALWAYS RETURN TO ITS POSITION WHEN MOVING IT
    if(cursor > CONSOLE_X_DIM * CONSOLE_Y_DIM || cursor < CONSOLE_X_DIM * (CONSOLE_Y_DIM - 1)) {
        //resets the cursor position
        swapLines();
        cursor = CONSOLE_X_DIM * (CONSOLE_Y_DIM - 1);
    }
    int i = CONSOLE_Y_DIM;
    int j = cursor % CONSOLE_X_DIM;
    putC(c);
    *console[i][j] = c;
}

void reprintLine(int line) {
    int aux = cursor;
    int i = line * CONSOLE_X_DIM;
    _moveCursor(i);
    for(int j=0; j<CONSOLE_X_DIM; j++) {
        putC(*console[i][j]);
    }
    cursor = aux;
}

void clearLine(int line) {
    int aux = cursor;
    int cursorPos = line * CONSOLE_X_DIM;
    _moveCursor(cursorPos);
    for(int i=0; i<CONSOLE_X_DIM; i++) {
        *console[line][i] = ' ';
        putC(' ');
    }
    cursor = aux;
}

void swapLines() {
    cLine* aux = console[0];
    for(int i=0; i<pAmount-1; i++) {
        console[i] = console[i+1];
        reprintLine(i);
    }
    console[CONSOLE_Y_DIM - 1] = aux;
    clearLine(CONSOLE_Y_DIM);
}

// ################## CONSOLE #####################
