#include <programs.h>
#include <standardLib.h>

typedef void (*FunctionPtr)();

struct PROGRAM_STRUCT {
    char* name_id;
    char* description;
    FunctionPtr program;
}PROGRAM_STRUCT;

typedef struct PROGRAM_STRUCT* Program;

void unknownCommand(char* str);

void help(), testExceptions(), showRegisters(), playBubbles(), playPong();

static Program pArr[] = {
        &(struct PROGRAM_STRUCT){"help", "displays all available commands", help},
        &(struct PROGRAM_STRUCT){"ex_test", "runs an exception test", testExceptions},
        &(struct PROGRAM_STRUCT){"registers", "shows the state of the system's registers", showRegisters},
        &(struct PROGRAM_STRUCT){"bubbles", "shows colored bubbles on the screen", playBubbles},
        &(struct PROGRAM_STRUCT){"pong", "runs a virtual ping pong match against the computer", playPong}
        };

//this value needs to be changed manually for now
static int pAmount = 5;

void parseCommand(char* str) {
    for(int i=0;i<pAmount;i++){
        if(compstring(str,pArr[i]->name_id)==0){
            pArr[i]->program();
            return;
        }
    }
    unknownCommand(str);
}

void unknownCommand(char* str) {
    printFormat("\nUnknown command:\n\t'%s'\nType 'help' for a list of available commands.\n\n", str);
}

void help() {
    for(int i=0;i<pAmount;i++){
        printFormat("%s: %s \n",pArr[i]->name_id,pArr[i]->description);
    }
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
