#include <stdarg.h>
#include "printf.h"
char *currentVM = (char *)0xb8000;
void printf(const char *format, ...){
    va_list args;
    va_start(args, format);
    char attr = 0x0a;
    
    while(*format){
        if(*format != '%'){
            if(*format == '\n'){
                currentVM += (80 - ((currentVM - (char *)0xb8000) / 2) % 80) * 2;
            } else {
                printChar(currentVM, *format, attr);
                currentVM += 2;
            }
            format++;
            continue;
        }
        format++; // skip '%'
        
        switch(*format){
            case 's': {
                const char *str = va_arg(args, const char *);
                printString(currentVM, str, attr);
                currentVM += strlen(str) * 2;
                break;
            }
            case 'c': {
                char c = (char)va_arg(args, int);
                printChar(currentVM, c, attr);
                currentVM += 2;
                break;
            }
            case 'd': {
                int num = va_arg(args, int);
                printInt(currentVM, num, 10, attr);
                char buf[12];
                itoa(num, buf, 10);
                currentVM += strlen(buf) * 2;
                break;
            }
            case 'x': {
                int num = va_arg(args, int);
                printInt(currentVM, num, 16, attr);
                char buf[12];
                itoa(num, buf, 16); 
                currentVM += strlen(buf) * 2;
                break;
            }
            default:
                printChar(currentVM, '%', attr);
                currentVM += 2;
                printChar(currentVM, *format, attr);
                currentVM += 2;
                break;
        }
        format++;
    }
    va_end(args);
}

static void printChar(char *currentVM, char c, char attr){
    *currentVM = c;
    *(currentVM + 1) = attr;
}

static void printString(char *currentVM, const char *str, char attr){
    while(*str){
        printChar(currentVM, *str, attr);
        currentVM += 2;
        str++;
    }
}

static void printInt(char *currentVM, int num, int base, char attr){
    char buf[32];
    itoa(num, buf, base);
    printString(currentVM, buf, attr);
}

static char *itoa(int value, char *str, int base){
    char *ptr = str;
    char *digits = "0123456789abcdef";
    int isNeg = 0;
    
    if(value < 0 && base == 10){
        isNeg = 1;
        value = -value;
    }
    
    do {
        *ptr++ = digits[value % base];
        value /= base;
    } while(value);
    
    if(isNeg){
        *ptr++ = '-';
    }
    *ptr = '\0';
    //reverse the string
    char *start = str;
    char *end = ptr - 1;
    while(start < end){
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    
    return str;
}

static int strlen(const char *str){
    int len = 0;
    while(*str++) len++;
    return len;
}