#include <standardLib.h>
#include <stdarg.h>
#include <system.h>
#define SYSWRITE 0
#define SYSREAD 1

int getDigits(int n);
void _printDec(int value, int len, uint8_t padding0, char* buff);
void _printHex(uint64_t value, char* buff);

static char * itoa( uint64_t value, char * str, int base )
// code taken from https://wiki.osdev.org/Printing_To_Screen
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base]; //???????
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void putChar(char c){ //a partir del segundo parametro no importa lo que le ponga
    interrupt(SYSWRITE,(uint64_t) &c,1,0,0,0);
}

static void putStrn(char*s){
    int i;
    for(i=0;s[i]!='\0';i++){
        i++;
    }
    interrupt(SYSWRITE, (uint64_t)s, i, 0, 0, 0);
}

char getChar(){
    char c;
    //this prevents the system calls from being blocked by the sys_read interruption
    while(1) {
        if(keyPress()) {
            interrupt(SYSREAD,(uint64_t)&c,0,0,0,0);
            return c;
        }
    }
}
void printFormat(const char* format, ...) {
    char buff[17];
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Move past '%'
            int len = 0;
            uint8_t padding0 = 0;
            if(*format == '0') {
                padding0 = 1;
                format++;
            }
            if(*format >= '1' && *format <= '9') {
                len = *format - '0';
                format++;
            }
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    _printDec(value, len, padding0, buff);
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    putStrn(value);
                    break;
                }
                case 'x':{
                    format++;
                    uint64_t value =va_arg(args,uint64_t);
                    _printHex(value, buff);
                    break;
                }
                default: {
                    putChar(*format);
                    break;
                }
            }
        } else {
            putChar(*format);
        }
        format++; // Move to the next character
    }
    va_end(args);
}

int _pow(int base, int power) {
    //this can't handle a negative power value
    if(power <= 0) {
        return 1;
    }
    int result = base;
    for(int i=0; i< power - 1; i++) {
        result = result * base;
    }
    return result;
}

void _printDec(int value, int len, uint8_t padding0, char* buff) {
    int digits=getDigits(value);
    int zeros;
    while(digits > len) {
        //example: 4567 -> 567
        int place = _pow(10, digits - 1);// place = 10^(4-1) = 1000
        int num = value / place;        // num = 4567 / 1000 = 4
        value = value - place * num;   // value = 4567 - (1000 * 4) = 567
        digits--;
        padding0=0;
    }
    if(len > 0 && padding0) {
        //how many zeros need to be placed before writing the number
        zeros = len - digits;
        for(int i=0; i<zeros; i++) {
            putChar('0');
        }
    }
    putStrn(itoa(value,buff,10));
}

void _printHex(uint64_t value, char* buff) {
    putStrn("0x");
    putStrn(itoa(value,buff,16));
}

int compString(const char*s1,const char*s2){
    while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;
	return (*s1 - *--s2);
}

int getDigits(int n){
    int digits=0;
    while(n!=0){
        n=n/10;
        digits++;
    }
    return digits;
}
