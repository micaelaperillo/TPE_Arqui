#include <programs.h>

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

void setupProgram();

void help(), testExceptions(), showRegisters(), playBubbles(), playPong();

void parseCommand(char* str) {
    //TODO implementar
}

void loadCommands() {
    setupProgram("help", "displays all available commands", help);
    setupProgram("ex_test", "creates and tests the exceptions", testExceptions);
    setupProgram("registers", "shows the state of the system's registers", showRegisters);
    setupProgram("bubbles", "shows colored bubbles on the screen", playBubbles);
    setupProgram("pong", "runs a virtual ping pong match against the machine", playPong);
}

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

void testExcpetions() {
    //TODO implementar
}

void showRegisters() {
    //TODO implementar
}

void playBubbles() {
    bubbles();
}

