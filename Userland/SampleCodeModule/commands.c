#include <programs.h>
#include <standardLib.h>

#define MAX_PROGRAMS 20
typedef void (*FunctionPtr)();

struct PROGRAM_STRUCT {
    char* name_id;
    char* description;
    FunctionPtr program;
}PROGRAM_STRUCT;

typedef struct PROGRAM_STRUCT* Program;

void setupProgram();
void unknownCommand(char* str);

void help(), testExceptions(), showRegisters(), playBubbles(), playPong();

static Program pArr[] = {
        &(struct PROGRAM_STRUCT){"help", "displays all available commands", help},
        &(struct PROGRAM_STRUCT){"ex_test", "runs an exception test", testExceptions},
        &(struct PROGRAM_STRUCT){"registers", "shows the state of the system's registers", showRegisters},
        &(struct PROGRAM_STRUCT){"bubbles", "shows colored bubbles on the screen", playBubbles},
        &(struct PROGRAM_STRUCT){"pong", "runs a virtual ping pong match against the computer", playPong}
        };

static int pAmount = 5;

void parseCommand(char* str) {
    //TODO implementar
    unknownCommand(str);
}

void unknownCommand(char* str) {
    printFormat("\nUnknown command:\n\t'%s'\nType 'help' for a list of available commands.\n\n", str);
    putChar('\n');
    printFormat("%s\n", pArr[0]->name_id);
}

void help() {
    //TODO : recorre pList e imprime los comandos y su descripcion
}

void testExceptions() {
    //TODO implementar
}

void showRegisters() {
    //TODO implementar
}

void playBubbles() {
    bubbles();
}

void playPong() {
    //TODO implementar
}
