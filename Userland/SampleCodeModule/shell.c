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

#define CONSOLE_X_DIM 96

typedef char cLine[CONSOLE_X_DIM];
static cLine prompt;



void startShell() {
    //PROGRAMS SETUP
    setupProgram("help", "displays all available commands", help);

}


// ################## CONSOLE #####################
