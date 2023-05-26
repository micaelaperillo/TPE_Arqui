#include <standardLib.h>
#include <stdarg.h>
#define SYSWRITE 0
#define SYSREAD 1

static char * itoa( int value, char * str, int base ) //puede ser util para printf
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
    char* aux={&c};
    interrupt(SYSWRITE,aux,1,0,0,0);
}
static void putStrn(char*s){
    for(int i =0;s[i]!='\0';i++){
        putChar(s[i]);
    }
}

char getChar(){
    char c;
    interrupt(SYSREAD,&c,1,0,0,0);
    return c;
}
void printEfe(const char* format, ...) {
    char* buff[9];
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    putStrn(itoa(value,buff,10));
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    putStrn(value);
                    break;
                }

                default:
                    putChar(*format);
                    break;
            }
        } else {
            putChar(*format);
        }
        format++; // Move to the next character
    }
    va_end(args);
}

int compstring(const char*s1,const char*s2){
    int i,j;
    for (i=0,j=0;s1[i]!='\0' && s2[i]!='\0';i++,j++){
        if(s1[i]!=s2[j])
            return 0;
    }
    if(i!=j)
        return 0;
    return 1;
}
