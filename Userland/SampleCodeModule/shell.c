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
    promptDim = 0;
}

void writePromptIcon() {
    printFormat("$~");
}

void startShell() {
    putChar('\n');
    shellLoop();
}

void shellLoop() {
    //waits for input and stores it in prompt
    char c;
    writePromptIcon();
    while((c = getChar()) != 27 ) {// 'esc'
        if(c == '\n') {
            //executes the command
            putChar(c);
            parseCommand(prompt);
            clearPrompt();
            putChar('\n');
            writePromptIcon();
        }

        else if(c == '\b') {
            if(promptDim > 0) {
                putChar(c);
                prompt[--promptDim] = '\0';
            }
        }

        else if(promptDim < CONSOLE_X_DIM - 2){
            putChar(c);
            prompt[promptDim++] = c;
        }
    }
    clearScreen();
}
