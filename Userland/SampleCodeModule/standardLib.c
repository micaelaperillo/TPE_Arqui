/*#include <standardLib.h>
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
void putC(uint64_t c){ //a partir del segundo parametro no importa lo que le ponga
    interrupt(SYSWRITE,c,1,0,0,0);
}

char getC(){
    char c;
    interrupt(SYSREAD,&c,1,0,0,0);
    return c;
}
char* getS(){
    char*s;
    int i=0;
    while((s[i]=getC())!='\n'){
       putC((uint64_t)(s+i));
        i++;
    }
    s[i]='\0';
    return s;
}


*/
