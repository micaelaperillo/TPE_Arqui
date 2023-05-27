#include <programs.h>
#include <standardLib.h>
#include <graphics.h>
#include <timeDate.h>

typedef void (*FunctionPtr)();

struct PROGRAM_STRUCT {
    char* name_id;
    char* description;
    FunctionPtr program;
}PROGRAM_STRUCT;

typedef struct PROGRAM_STRUCT* Program;

void unknownCommand(char* str);

void help(), testExceptions(), showRegisters(), displayTime(), displayDate(), playBubbles(), playPong();

static Program pArr[] = {
        &(struct PROGRAM_STRUCT){"help", "displays all available commands", help},
        &(struct PROGRAM_STRUCT){"ex_test", "runs an exception test", testExceptions},
        &(struct PROGRAM_STRUCT){"registers", "prints the state of the system's registers", showRegisters},
        &(struct PROGRAM_STRUCT){"time", "prints the current time", displayTime},
        &(struct PROGRAM_STRUCT){"date", "prints the current date", displayDate},
        &(struct PROGRAM_STRUCT){"bubbles", "shows colored bubbles on the screen", playBubbles},
        &(struct PROGRAM_STRUCT){"pong", "runs a virtual ping pong match against the computer", playPong},
        null //marks the end of the array
        };

void parseCommand(char* str) {
    for(int i=0;pArr[i]!=null;i++){
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
    for(int i=0;pArr[i]!=null;i++){
        putChar('\n');
        printFormat("\t'%s': %s \n",pArr[i]->name_id,pArr[i]->description);
        putChar('\n');
    }
}

void testExceptions() {
    //TODO implementar
}

void showRegisters() {
    //TODO implementar
}

void displayTime() {
    printTime();
    putChar('\n');
}

void displayDate() {
    printDate();
    putChar('\n');
}

void playBubbles() {
    enableDoubleBuffering();
    bubbles();
}

void playPong() {
    //TODO implementar
}
