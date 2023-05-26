#include <commands.h>
#include <standardLib.h>
#define CONSOLE_X_DIM 96

typedef char cLine[CONSOLE_X_DIM];
static cLine prompt;
static int promptDim = 0;

void shellLoop();

void clearPrompt() {
    for(int i=0; i<CONSOLE_X_DIM; i++) {
        prompt[i] = '\0';
    }
}

void startShell() {
    loadCommands();
    shellLoop();
}


void shellLoop() {
    //waits for input and stores it in prompt
    char c;
    while((c = getC()) != 27 ) {// 'esc'
        if(c == '\n') {
            parseCommand(prompt);
        }
        else if(c == '\b' && promptDim > 0) {
            //borra
            prompt[promptDim--] = '\0';
        }
        else if(promptDim < CONSOLE_X_DIM){
            putC(c);
            prompt[promptDim++] = c;
        }
    }
}