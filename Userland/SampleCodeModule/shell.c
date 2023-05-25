#include <stdint.h>

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
#define CONSOLE_X_CHAR 128
#define CONSOLE_Y_CHAR 96

typedef char cLine[CONSOLE_X_CHAR];

static cLine* console[CONSOLE_Y_CHAR];
static cLine cPrompt;

void clearLine(cLine l);


void setupConsole() {
    //clears all the values
    clearLine(cPrompt);
    for(int i=0; i<CONSOLE_Y_CHAR; i++) {
        clearLine(*console[i]);
    }
}

void startShell() {
    //PROGRAMS SETUP
    setupProgram("help", "displays all available commands", help);

    //INITIALIZATIONS
    setupConsole();

    //STARTS THE CONSOLE
}

void clearLine(cLine l) {
    for(int i=0; i<CONSOLE_X_CHAR; i++) {
        l[i] = ' ';
    }
}

void swapLines() {
    cLine* aux = console[0];
    for(int i=0; i<pAmount-1; i++) {
        console[i] = console[i+1];
    }
    console[20] = aux;
    clearLine(*console[20]);

    //TODO reescribir todas las lineas
}

// ################## CONSOLE #####################
