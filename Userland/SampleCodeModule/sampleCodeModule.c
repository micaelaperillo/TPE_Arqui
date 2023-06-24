/* sampleCodeModule.c */

#include <shell.h>
#include <standardLib.h>
#include <graphics.h>


int main() {
    //in case an exception happens when using double buffering
    disableDoubleBuffering();
    printFormat("Initializing Shell\n");
    startShell();
    return 0;
}
