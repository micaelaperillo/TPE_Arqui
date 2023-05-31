#include <stdint.h>

extern unsigned char keydown();
extern unsigned char keypress();

#define LSHIFT 0x2A
#define RSHIFT 0x36
#define CAPS_LOCK 0x3A

#define NO_INPUT 0x00

#define TRUE 1
#define FALSE 0

static uint8_t shift = FALSE;
static uint8_t caps_lock = FALSE;

uint8_t lastKey = NO_INPUT;

const unsigned char kbdusNoShift[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd',
    'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const unsigned char kbdusWithShift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S', 'D',
    'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '|', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t keyPressed() {
    lastKey = keypress();
    return lastKey;
}

unsigned char retrieveChar(uint8_t keycode) {
    unsigned char c = (lastKey == NO_INPUT)?(kbdusNoShift[keycode]):(lastKey);
    lastKey = NO_INPUT;
    uint8_t isLetter = (c >= 'a' && c <= 'z');
    uint8_t auxShift = (caps_lock && isLetter)?(!shift):(shift);

    if(auxShift) {
        return kbdusWithShift[keycode];
    }
    return c;
}

uint8_t keyboard_handler() {
    unsigned char code = keydown();
    uint8_t keyRelease = FALSE;
    unsigned char keycode = code & 0x7F;//no diferencia entre release o no

    if(code & 0x80) {
        keyRelease = TRUE;
    }
    if(keycode == LSHIFT || keycode == RSHIFT) {
        shift = (keyRelease)?(FALSE):(TRUE);
    }
    else if(keycode == CAPS_LOCK) {
        caps_lock = (keyRelease)?(caps_lock):(!caps_lock);
    }
    else if(!keyRelease) {
        return retrieveChar(keycode);
    }
    return NO_INPUT;
}

char getc(){
    uint8_t c = keyboard_handler();

    while( c == NO_INPUT) {
        c = keyboard_handler();
    }
    return (char) c;
}

void gets(char * s) {
    int i = 0;
    char c;
    while((c=keyboard_handler())!='\n') {
        s[i] = c; //lee hasta el enter supuestamente
        i++;
    }
    s[i]='\0';
}
