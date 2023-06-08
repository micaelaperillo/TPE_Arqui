#include <programs.h>
#include <standardLib.h>
#include <graphics.h>
#include <timeDate.h>
#include <system.h>


typedef void (*FunctionPtr)();

struct PROGRAM_STRUCT {
    char* name_id;
    char* description;
    FunctionPtr program;
}PROGRAM_STRUCT;

typedef struct PROGRAM_STRUCT* Program;

extern void invalidOp();

void unknownCommand(char* str);

void help(), testException0(),testException6(), displayTime(), displayDate(), playBubbles(), playPong(), playBeep();

static Program pArr[] = {
        &(struct PROGRAM_STRUCT){"help", "displays all available commands", help},
        &(struct PROGRAM_STRUCT){"test-div0", "runs a zero division", testException0},
        &(struct PROGRAM_STRUCT){"test-invalidop", "runs an invalid op", testException6},
        &(struct PROGRAM_STRUCT){"time", "prints the current time", displayTime},
        &(struct PROGRAM_STRUCT){"date", "prints the current date", displayDate},
        &(struct PROGRAM_STRUCT){"bubbles", "shows colored bubbles on the screen", playBubbles},
        &(struct PROGRAM_STRUCT){"pong", "runs a virtual ping pong match against the computer", playPong},
        &(struct PROGRAM_STRUCT){"beep", "produces a 'beep' sound", playBeep},
        null //marks the end of the array
        };

void parseCommand(char* str) {
    for(int i=0;pArr[i]!=null;i++){
        if(compString(str,pArr[i]->name_id)==0){
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

void testException0() {
   int i=1/0;
}

void testException6(){
    invalidOp();
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
    clearScreen();
    disableDoubleBuffering();
}

void playPong() {
    enableDoubleBuffering();
    pong();
    clearScreen();
    disableDoubleBuffering();
}

void playBeep() {
    play_beep(2000, 100);
}
