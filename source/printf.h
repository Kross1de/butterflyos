#ifndef PRINTF_H
#define PRINTF_H
void printf(const char *format, ...);
static void printChar(char *videomem, char c, char attr);
static void printString(char *videomem, const char *str, char attr);
static void printInt(char *videomem, int num, int base,  char attr);
static char *itoa(int value, char *str, int base);
static int strlen(const char *str);
extern char *currentVM;
#endif