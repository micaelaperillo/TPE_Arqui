#include <commands.h>
#include <graphics.h>
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

void writePromptIcon() {
    //TODO pasarlo a putS
    putC('$');
    putC('~');
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
            //executes the command
            putC(c);
            clearPrompt();

            parseCommand(prompt);

            //if the command used graphics, it's better to clear them out just in case
            clearScreen();
            writePromptIcon();
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